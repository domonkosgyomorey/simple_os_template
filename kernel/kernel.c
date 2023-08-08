#include "../shell/shell.h"
#include "../hdep/isr.h"
#include "../drivers/keyboard.h"
#include "../hdep/timer.h"
#include "../libc/string.h"
#include "../drivers/gs320200.h"
#include "../hdep/types.h"
#include "kernel.h"

u32 graphics_mode;

void print_in_hex(int num){
    char h[16] = {'0', '1', '2','3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    char buff[100];
    for(int i = 0; i < 32; i+=4){
        buff[i/4] = h[((num>>i)&0b1111)];
    }
    str_reverse(buff);
    shell_print("0x");
    shell_print(buff);
    shell_print("\n");
}

void update(u32 frames){
    for (u32 i = 0; i < GS320200_HEIGHT; i++){
        for (u32 j = 0; j < GS320200_WIDTH; j++){
            gs320200_draw_point(j, i, (~(i&j)-frames));
        } 
    }
}

extern void* __init_funcs;
extern void* __init_funcs_end;

void main() {
    asm("mov %0, %%eax":"=r"(graphics_mode)::);
    
    isr_install();
    enable_interrupts();

    kernel_init_fun_t* fn_ptr = (kernel_init_fun_t*)&__init_funcs;
    while((u32)fn_ptr-(u32)&__init_funcs_end){
        (*fn_ptr++)();
    }

    if(add_keyboard_callback(&shell_key_callback)<0){
        if(graphics_mode==2){
            shell_print("Failed to add a keyboard callback\n");
        }else{
            gs320200_draw_error(GS320200_RED);
        }
    }

    if(pit_add_tick_callback(&update)<0){
        if(graphics_mode==2){
            shell_print("Failed to add a tick callback\n");
        }else{
            gs320200_draw_error(GS320200_RED);
        }
    }
 
}