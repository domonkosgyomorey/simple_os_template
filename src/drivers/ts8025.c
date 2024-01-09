#include "drivers/ts8025.h"
#include "kernel/ports.h"
#include "libc/stdlib.h"

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
        offset = ts8025_print_char(message[i++], col, row, TS8025_WHITE_ON_BLACK);
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
    ts8025_print_char(TS8025_BACKSPACE, col, row, TS8025_WHITE_ON_BLACK);
}


int ts8025_print_char(char c, int col, int row, char attr) {
    u8* vidmem = (u8*) TS8025_VIDEO_ADDRESS;
    if (!attr) attr = TS8025_WHITE_ON_BLACK;

    if (col >= TS8025_MAX_COLS || row >= TS8025_MAX_ROWS) {
        vidmem[2*(TS8025_MAX_COLS)*(TS8025_MAX_ROWS)-2] = 'E';
        vidmem[2*(TS8025_MAX_COLS)*(TS8025_MAX_ROWS)-1] = TS8025_RED_ON_WHITE;
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

    if (offset >= TS8025_MAX_ROWS * TS8025_MAX_COLS * 2) {
        int i;
        for (i = 1; i < TS8025_MAX_ROWS; i++) 
            memncpy((int*)(get_offset(0, i) + TS8025_VIDEO_ADDRESS),
                        (int*)(get_offset(0, i-1) + TS8025_VIDEO_ADDRESS),
                        TS8025_MAX_COLS * 2);

        char* last_line = (char*) (get_offset(0, TS8025_MAX_ROWS-1) + (u8*) TS8025_VIDEO_ADDRESS);
        for (i = 0; i < TS8025_MAX_COLS * 2; i++) last_line[i] = 0;

        offset -= 2 * TS8025_MAX_COLS;
    }

    set_cursor_offset(offset);
    return offset;
}

int get_cursor_offset() {
    outb(TS8025_REG_SCREEN_CTRL, 14);
    int offset = inb(TS8025_REG_SCREEN_DATA) << 8;
    outb(TS8025_REG_SCREEN_CTRL, 15);
    offset += inb(TS8025_REG_SCREEN_DATA);
    return offset * 2;
}

void set_cursor_offset(int offset) {
    offset /= 2;
    outb(TS8025_REG_SCREEN_CTRL, 14);
    outb(TS8025_REG_SCREEN_DATA, (u8)(offset >> 8));
    outb(TS8025_REG_SCREEN_CTRL, 15);
    outb(TS8025_REG_SCREEN_DATA, (u8)(offset & 0xff));
}

void ts8025_clear_screen() {
    int screen_size = TS8025_MAX_COLS * TS8025_MAX_ROWS;
    int i;
    u8* screen = (u8*) TS8025_VIDEO_ADDRESS;

    for (i = 0; i < screen_size; i++) {
        screen[i*2] = ' ';
        screen[i*2+1] = TS8025_WHITE_ON_BLACK;
    }
    set_cursor_offset(get_offset(0, 0));
}


int get_offset(int col, int row) { return 2 * (row * TS8025_MAX_COLS + col); }
int get_offset_row(int offset) { return offset / (2 * TS8025_MAX_COLS); }
int get_offset_col(int offset) { return (offset - (get_offset_row(offset)*2*TS8025_MAX_COLS))/2; }
