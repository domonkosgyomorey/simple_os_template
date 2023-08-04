#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../x86_64/types.h"

#define MAX_KEYBOARD_CALLBACK   32
#define ESCAPE                  0x1
#define BACKSPACE               0x0E
#define TAB                     0xF
#define ENTER                   0x1C
#define LEFT_CTRL               0x1D
#define LEFT_SHIFT              0x2A
#define RIGHT_SHIFT             0x36
#define KEYPAD_MUL              0x37
#define LEFT_ALT                0x38
#define SCANCODE_MAX            88
#define MAX_C_PER_LINE          256

typedef void (*keyboard_callback)(u8, u8, const char*);
void init_keyboard();
s8 add_keyboard_callback(keyboard_callback keyboard_cb);

#endif // KEYBAORD_H