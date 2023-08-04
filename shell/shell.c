#include "../x86_64/types.h"
#include "../drivers/keyboard.h"
#include "../drivers/vga8025.h"
#include "../libc/string.h"
#include "../libc/stdlib.h"
#include "shell.h"

static char key_buffer[MAX_C_PER_LINE];
u8 line_len = 0;

const char* shell_commands[] = {
    "ECHO"
};
typedef enum shell_command{
    SHELL_CMD_ECHO = 0,
    SHELL_CMD_COUNT
}shell_command;

void shell_print(s8* msg){
    vga8025_print(msg);
}

void shell_key_callback(u8 letter, u8 scancode, const char* name) {
    if (scancode > SCANCODE_MAX ) return;
    if (scancode == BACKSPACE ) {
        backspace(key_buffer);
        vga8025_print_backspace();
        --line_len;
    } else if(line_len == MAX_C_PER_LINE-1){
        return;
    } else if (scancode == ENTER) {
        vga8025_print("\n");
        shell_command_handler(key_buffer);
        vga8025_print("# ");
        key_buffer[0] = '\0';
        line_len=0;
    } else {
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        vga8025_print(str);
        ++line_len;
    }
    (void)(name);
}

void shell_command_handler(s8* msg){
    if(strnequ(msg, shell_commands[SHELL_CMD_ECHO], 4)){
        vga8025_print("ECHO: ");
        vga8025_print(msg);
        vga8025_print("\n");
    }
}