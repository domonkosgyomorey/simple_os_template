#ifndef TS8025_H
#define TS8025_H

#include "libc/types.h"

#define TS8025_VIDEO_ADDRESS   0xB8000
#define TS8025_MAX_ROWS 25
#define TS8025_MAX_COLS 80
#define TS8025_WHITE_ON_BLACK  0xF
#define TS8025_RED_ON_WHITE    0xF4

#define TS8025_BACKSPACE       0x08

#define TS8025_REG_SCREEN_CTRL 0x3D4
#define TS8025_REG_SCREEN_DATA 0x3D5

void ts8025_clear_screen();
void ts8025_print_at(const char *message, int col, int row);
void ts8025_print(const char *message);
void ts8025_print_backspace();

#endif // TS8025_H
