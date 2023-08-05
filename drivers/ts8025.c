#include "ts8025.h"
#include "../hdep/ports.h"
#include "../libc/stdlib.h"

int get_cursor_offset();
void set_cursor_offset(int offset);
int ts8025_print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

void ts8025_print_at(const char *message, int col, int row) {
    int offset;
    if (col>=0&&row>=0){
        offset = get_offset(col, row);
    } else {
        offset = get_cursor_offset();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    int i = 0;
    while (message[i]!=0) {
        offset = ts8025_print_char(message[i++], col, row, WHITE_ON_BLACK);
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

void ts8025_print(const char *message) {
    ts8025_print_at(message, -1, -1);
}

void ts8025_print_backspace() {
    int offset = get_cursor_offset()-2;
    int row = get_offset_row(offset);
    int col = get_offset_col(offset);
    ts8025_print_char(VGA_BACKSPACE, col, row, WHITE_ON_BLACK);
}


int ts8025_print_char(char c, int col, int row, char attr) {
    u8* vidmem = (u8*) VIDEO_ADDRESS;
    if (!attr) attr = WHITE_ON_BLACK;

    if (col >= MAX_COLS || row >= MAX_ROWS) {
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-2] = 'E';
        vidmem[2*(MAX_COLS)*(MAX_ROWS)-1] = RED_ON_WHITE;
        return get_offset(col, row);
    }

    int offset;
    if (col >= 0 && row >= 0) offset = get_offset(col, row);
    else offset = get_cursor_offset();

    if (c == '\n') {
        row = get_offset_row(offset);
        offset = get_offset(0, row+1);
    } else if (c == 0x08) {
        vidmem[offset] = ' ';
        vidmem[offset+1] = attr;
    } else {
        vidmem[offset] = c;
        vidmem[offset+1] = attr;
        offset += 2;
    }

    if (offset >= MAX_ROWS * MAX_COLS * 2) {
        int i;
        for (i = 1; i < MAX_ROWS; i++) 
            memncpy((int*)(get_offset(0, i) + VIDEO_ADDRESS),
                        (int*)(get_offset(0, i-1) + VIDEO_ADDRESS),
                        MAX_COLS * 2);

        char* last_line = (char*) (get_offset(0, MAX_ROWS-1) + (u8*) VIDEO_ADDRESS);
        for (i = 0; i < MAX_COLS * 2; i++) last_line[i] = 0;

        offset -= 2 * MAX_COLS;
    }

    set_cursor_offset(offset);
    return offset;
}

int get_cursor_offset() {
    outb(REG_SCREEN_CTRL, 14);
    int offset = inb(REG_SCREEN_DATA) << 8;
    outb(REG_SCREEN_CTRL, 15);
    offset += inb(REG_SCREEN_DATA);
    return offset * 2;
}

void set_cursor_offset(int offset) {
    offset /= 2;
    outb(REG_SCREEN_CTRL, 14);
    outb(REG_SCREEN_DATA, (u8)(offset >> 8));
    outb(REG_SCREEN_CTRL, 15);
    outb(REG_SCREEN_DATA, (u8)(offset & 0xff));
}

void ts8025_clear_screen() {
    int screen_size = MAX_COLS * MAX_ROWS;
    int i;
    u8* screen = (u8*) VIDEO_ADDRESS;

    for (i = 0; i < screen_size; i++) {
        screen[i*2] = ' ';
        screen[i*2+1] = WHITE_ON_BLACK;
    }
    set_cursor_offset(get_offset(0, 0));
}


int get_offset(int col, int row) { return 2 * (row * MAX_COLS + col); }
int get_offset_row(int offset) { return offset / (2 * MAX_COLS); }
int get_offset_col(int offset) { return (offset - (get_offset_row(offset)*2*MAX_COLS))/2; }