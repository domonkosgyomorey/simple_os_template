#ifndef SHELL_H
#define SHELL_H

#include "../hdep/types.h"

#define CMD_MAX_SIZE 10
#define ARG_MAX_SIZE 25
#define MAX_ARGS_NUM 10

typedef enum shell_command{
    SHELL_CMD_ECHO = 0,
    SHELL_CMD_LS,
    SHELL_CMD_EXIT,
    SHELL_CMD_CLEAR,
    SHELL_CMD_COUNT
}shell_command;

void shell_key_callback(u8 letter, u8 scancode, const char* name);
void shell_print(s8* msg);
void shell_print_in_hex(s32 num);

#endif