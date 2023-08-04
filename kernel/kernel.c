#include "../shell/shell.h"
#include "../x86_64/isr.h"
#include "../drivers/keyboard.h"
#include "../x86_64/timer.h"
#include "../libc/string.h"

void tick_fun(u32 n){
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
    init_timer(50);
    if(add_keyboard_callback(&shell_key_callback)<0){
        shell_print("Failed to add a keyboard callback\n");
    }

    char* text = "    This is a text";
    char text_cpy[100];
    str_cpy(text, text_cpy);
    str_trim(text);
    shell_print(text);
    shell_print("\n");
    shell_print(text_cpy);
    shell_print("\n");

    str_cpy(text_cpy, text);
    char arg[25];
    str_cut_word(text_cpy, arg);
    shell_print(text_cpy);
    shell_print("\n");
    shell_print(arg);
    shell_print("\n");
    str_cut_word(text_cpy, arg);
    shell_print(text_cpy);
    shell_print("\n");
    shell_print(arg);
    shell_print("\n");

    shell_print("# ");
}