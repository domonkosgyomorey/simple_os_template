#include "../hdep/types.h"
#include "../drivers/keyboard.h"
#include "../drivers/vga8025.h"
#include "../libc/string.h"
#include "../libc/stdlib.h"
#include "shell.h"

static char key_buffer[MAX_C_PER_LINE];
u8 line_len = 0;

const char shell_commands[][CMD_MAX_SIZE] = {
    "ECHO",
    "LS",
    "EXIT",
    "CLEAR",
};


void shell_command_handler(s8* msg);

void shell_print(s8* msg){
    vga8025_print(msg);
}

void shell_key_callback(u8 letter, u8 scancode, const char* name) {
    if (scancode > SCANCODE_MAX ) return;
    if (scancode == BACKSPACE) {
        if(str_len(key_buffer)!=0){
            str_backspace(key_buffer);
            vga8025_print_backspace();
            --line_len;
        }
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
        str_append(key_buffer, letter);
        vga8025_print(str);
        ++line_len;
    }
    (void)(name);
}

void shell_command_handler(s8* msg){
    char command[CMD_MAX_SIZE];
    char args[MAX_ARGS_NUM][ARG_MAX_SIZE];
    str_cut_word_n(msg, command, CMD_MAX_SIZE);
    int i = 0;
    do{
        str_cut_word_n(msg, args[i], ARG_MAX_SIZE);
    }while(str_len(args[i++])!=0);
    if(str_equ(command, shell_commands[SHELL_CMD_ECHO])){
        vga8025_print("ECHO: ");
        vga8025_print(args[0]);
        vga8025_print("\n");
    }else if(str_equ(command, shell_commands[SHELL_CMD_LS])){
        vga8025_print("LS: NOT IMPLEMENTED YET");
        vga8025_print("\n");
    }else if(str_equ(command, shell_commands[SHELL_CMD_EXIT])){
        vga8025_print("EXIT: BYE");
        asm volatile("hlt");
    }else if(!str_len(command)){
    }else if(str_equ(command, shell_commands[SHELL_CMD_CLEAR])){
        vga8025_clear_screen();
    }else{
        vga8025_print(command);
        vga8025_print(" command does not supported.");
        vga8025_print("\n");
    }
}