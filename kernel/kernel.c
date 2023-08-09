#include "../shell/shell.h"
#include "../drivers/keyboard.h"
#include "../hdep/timer.h"
#include "../libc/string.h"
#include "../drivers/gs320200.h"
#include "../hdep/types.h"
#include "kernel.h"

u32 graphics_mode;

void update(u32 frames){
    if(graphics_mode==0x13){
        for (u32 i = 0; i < GS320200_HEIGHT; i++){
            for (u32 j = 0; j < GS320200_WIDTH; j++){
                gs320200_draw_point(j, i, ~(i&j)-frames);
            } 
        }
    }
}

extern void* __init_funcs;
extern void* __init_funcs_end;

void main() {
    asm("mov %0, %%eax":"=r"(graphics_mode));

    u32 init_fn_size = ((u32)&__init_funcs_end-(u32)&__init_funcs)/sizeof(kernel_init_fun_s);
    
    kernel_init_fun_s* fn_ptr;
    for(u32 i = 0; i < KERNEL_INIT_PRIORITY_COUNT; ++i){
        u32 j = 0;
        fn_ptr = (kernel_init_fun_s*)&__init_funcs;
        while(j<init_fn_size){
            if(fn_ptr->priority==i){
                fn_ptr->init_fun();
                shell_print_in_hex(fn_ptr->priority);
            }
            fn_ptr++;
            j++;
        }
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