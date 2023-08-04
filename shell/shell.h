#ifndef SHELL_H
#define SHELL_H

#include "../x86_64/types.h"

void shell_key_callback(u8 letter, u8 scancode, const char* name);
void shell_print(s8* msg);
void shell_command_handler(s8* msg);

#endif