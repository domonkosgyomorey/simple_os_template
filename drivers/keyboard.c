#include "../hdep/ports.h"
#include "../hdep/isr.h"
#include "../libc/stdlib.h"
#include "keyboard.h"
#include "../kernel/kernel.h"

keyboard_callback keyboard_callbacks[MAX_KEYBOARD_CALLBACK];
u8 keyboard_callback_count = 0;

_init_driver_attrib kernel_init_fun_t init_keyboard_t = &init_keyboard;

const char* scancode_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar", "CapsLock", "F1", 
        "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "NumLock", "ScrollLock", "Keypad 7",
        "Keypad 8", "Keypad 9", "Keypad -", "Keypad 4", "Keypad 5", "Keypad 6", "Keypad +", "Keypad 1",
        "Keypad 2", "Keypad 3", "Keypad 0", "Keypad .", "?", "?", "?", "F11", "F12"};
const char scancode_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '*', '?', ' ', '?', '?', '?', '?', '?', '?', '?',
        '?', '?', '?', '?', '?', '?', '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3',
        '0', '.', '?', '?', '?', '?', '?'};

static void keyboard_handler_callback(registers_t regs){
    u8 scancode = inb(0x60);
    u8 letter = scancode_ascii[(int)scancode];
    const char* name = scancode_name[(int)scancode];
    for(int i = 0; i < keyboard_callback_count; ++i){
        keyboard_callbacks[i](letter,scancode,name);
    }
    (void)(regs);
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_handler_callback); 
}

// return 1 on success and -1 on fail
s8 add_keyboard_callback(keyboard_callback keyboard_cb){
    if(keyboard_callback_count<MAX_KEYBOARD_CALLBACK){
        keyboard_callbacks[keyboard_callback_count++] = keyboard_cb;
        return 1;
    }else{
        return -1;
    }
} 