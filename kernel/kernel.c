#include "../shell/shell.h"
#include "../hdep/isr.h"
#include "../drivers/keyboard.h"
#include "../hdep/timer.h"
#include "../libc/string.h"

void tick_fun(int n){
    char t[6];
    int_to_ascii(n, t);
    int i = str_len(t);
    t[i] = '\n';
    t[i+1] = '\0';
    shell_print(t);
}

void main() {
    isr_install();
    enable_interrupts();

    init_keyboard();
    
    if(add_keyboard_callback(&shell_key_callback)<0){
        shell_print("Failed to add a keyboard callback\n");
    }

    // PIT (tick callback) test
    /*
    init_timer(50);
    if(add_tick_callback(&tick_fun)<0){
        shell_print("Failed to add a tick callback\n");
    }
    */

    shell_print("# ");
}