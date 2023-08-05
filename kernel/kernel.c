#include "../shell/shell.h"
#include "../hdep/isr.h"
#include "../drivers/keyboard.h"
#include "../hdep/timer.h"
#include "../libc/string.h"
#include "../drivers/gs320200.h"
#include "../hdep/types.h"

unsigned int graphics_mode;

void update(u32 frames){
    (void)frames;
    for (u32 i = 0; i < GS320200_HEIGHT; i++){
        for (u32 j = 0; j < GS320200_WIDTH; j++){
            gs320200_draw_point(j, i, ~(i&j)-frames);
        } 
    }
}

void main() {
    asm("mov %0, %%eax":"=r"(graphics_mode)::);
    isr_install();
    enable_interrupts(); 

    init_keyboard();
    
    if(add_keyboard_callback(&shell_key_callback)<0){
        if(graphics_mode==2){
            shell_print("Failed to add a keyboard callback\n");
        }else{
            gs320200_draw_error(GS320200_RED);
        }
    }

    // PIT (tick callback) test
    
    pit_init_timer(50);
    if(pit_add_tick_callback(&update)<0){
        if(graphics_mode==2){
            shell_print("Failed to add a tick callback\n");
        }else{
            gs320200_draw_error(GS320200_RED);
        }
    }

    char gm[10];
    int_to_ascii(graphics_mode, gm);
    shell_print(gm);
}