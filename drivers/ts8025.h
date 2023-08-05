#ifndef TS8025_H
#define TS8025_H

#include "../hdep/types.h"

#define VIDEO_ADDRESS   0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK  0xF
#define RED_ON_WHITE    0xF4

#define VGA_BACKSPACE       0x08

#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

void ts8025_clear_screen();
void ts8025_print_at(const char *message, int col, int row);
void ts8025_print(const char *message);
void ts8025_print_backspace();

#endif // TS8025_H
