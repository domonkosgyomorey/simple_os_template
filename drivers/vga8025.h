#ifndef SCREEN_H
#define SCREEN_H

#include "../x86_64/types.h"

#define VIDEO_ADDRESS 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0xF
#define RED_ON_WHITE 0xF4

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

void vga8025_clear_screen();
void vga8025_print_at(char *message, int col, int row);
void vga8025_print(char *message);
void vga8025_print_backspace();

#endif
