#include "../shell/shell.h"
#include "../x86_64/isr.h"
#include "../drivers/keyboard.h"
#include "../x86_64/timer.h"
#include "../libc/string.h"

void tick_fun(u32 n){
    char t[6];
    int_to_ascii(n, t);
    int i = strlen(t);
    t[i] = '\n';
    t[i+1] = '\0';
    shell_print(t);
}

void main() {
    isr_install();
    enable_interrupts();

    init_keyboard();
    init_timer(50);
    if(add_keyboard_callback(&shell_key_callback)<0){
        shell_print("Failed to add a keyboard callback\n");
    }
    
    char* text = "This is a kernel text for testing.";
    char db[10];
    int_to_ascii(strcountc(text, ' '), db);
    shell_print(db);
    shell_print("\n");
    
    if(add_tick_callback(tick_fun)<0){
        shell_print("Failed to add a tick callback\n");
    }
    
}