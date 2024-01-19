#include "shell/shell.h"
#include "drivers/keyboard.h"
#include "kernel/timer.h"
#include "libc/string.h"
#include "drivers/gs320200.h"
#include "libc/types.h"
#include "kernel/kernel.h"
#include "kernel/memory.h"

u32 graphics_mode;

void update(u32 frames){
    if(graphics_mode==0x13){
        for (u32 i = 0; i < GS320200_HEIGHT; i++){
            for (u32 j = 0; j < GS320200_WIDTH; j++){
                gs320200_draw_point(j, i, ~(i&j)-frames);
            } 
        }
    }
    gs320200_draw_rect(0,0,20,20,GS320200_CYAN);
    gs320200_swap_buffers();
}

void init_custom_callback(){
    if(add_keyboard_callback(&shell_key_callback)<0){
        if(graphics_mode==2){
            shell_print("Failed to add a keyboard callback\n");
        }
    }

    if(pit_add_tick_callback(&update)<0){
        if(graphics_mode==2){
            shell_print("Failed to add a tick callback\n");
        }
    }
}

// Pre-configured in the linker script
extern void* __init_funcs;
extern void* __init_funcs_end;

char* memory[1024];

void kernel_entry() {
    // Get the graphics mode, from a pre-configured space
    asm("mov %0, %%eax":"=r"(graphics_mode));

    initialize_memory(memory, 1024);

    int *num = (int*)buddy_allocate(sizeof(int));
    *num = 13;

    kernel_run_init_functions();

    init_custom_callback();

    shell_print("Value: ");
    shell_print_in_hex(*num);
    shell_print("\n");
    shell_print("Ptr: ");
    shell_print_in_hex((int)num);
    shell_print("\n");

    buddy_free(num);
}

void kernel_run_init_functions(){
    u32 init_fn_size = ((u32)&__init_funcs_end-(u32)&__init_funcs)/sizeof(kernel_init_fun_s);
    
    kernel_init_fun_s* fn_ptr;
    for(u32 i = 0; i < KERNEL_INIT_PRIORITY_COUNT; ++i){
        u32 j = 0;
        fn_ptr = (kernel_init_fun_s*)&__init_funcs;
        while(j<init_fn_size){
            if(fn_ptr->priority==i){
                fn_ptr->init_fun();
            }
            fn_ptr++;
            j++;
        }
    }
}