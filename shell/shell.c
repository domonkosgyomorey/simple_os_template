#include "../hdep/types.h"
#include "../drivers/keyboard.h"
#include "../drivers/ts8025.h"
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
    ts8025_print(msg);
}

void shell_key_callback(u8 letter, u8 scancode, const char* name) {
    if (scancode > SCANCODE_MAX ) return;
    if (scancode == BACKSPACE) {
        if(str_len(key_buffer)!=0){
            str_backspace(key_buffer);
            ts8025_print_backspace();
            --line_len;
        }
    } else if(line_len == MAX_C_PER_LINE-1){
        return;
    } else if (scancode == ENTER) {
        ts8025_print("\n");
        shell_command_handler(key_buffer);
        ts8025_print("# ");
        key_buffer[0] = '\0';
        line_len=0;
    } else {
        char str[2] = {letter, '\0'};
        str_append(key_buffer, letter);
        ts8025_print(str);
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
        ts8025_print("ECHO: ");
        ts8025_print(args[0]);
        ts8025_print("\n");
    }else if(str_equ(command, shell_commands[SHELL_CMD_LS])){
        ts8025_print("LS: NOT IMPLEMENTED YET");
        ts8025_print("\n");
    }else if(str_equ(command, shell_commands[SHELL_CMD_EXIT])){
        ts8025_print("EXIT: BYE");
        asm volatile("hlt");
    }else if(!str_len(command)){
    }else if(str_equ(command, shell_commands[SHELL_CMD_CLEAR])){
        ts8025_clear_screen();
    }else{
        ts8025_print(command);
        ts8025_print(" command does not supported.");
        ts8025_print("\n");
    }
}

void shell_print_in_hex(s32 num){
    char h[16] = {'0', '1', '2','3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    char buff[100];
    for(s32 i = 0; i < 32; i+=4){
        buff[i/4] = h[(num>>i)&0x0f];
    }
    str_reverse(buff);
    shell_print("0x");
    shell_print(buff);
    shell_print("\n");
}