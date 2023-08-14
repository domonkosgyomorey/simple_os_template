#include "gs320200.h"
#include "../libc/stdlib.h"
#include "../hdep/types.h"

u8* gs320200_back_buffer = (u8*)GS320200_ADDRESS;

void gs320200_draw_point(u32 x, u32 y, u8 color){
    gs320200_back_buffer[gs320200_get_offset(x, y)] = color;
}

void gs320200_draw_rect(u32 x, u32 y, u32 width, u32 height, u8 color){
    u32 offset = width*y+x;
    for(u32 i = 0; i < height; ++i){
        memset(gs320200_back_buffer+offset+i*GS320200_WIDTH, color, width);
    }    
}

void gs320200_swap_buffers(){
    u8* vid_addr = (u8*)GS320200_ADDRESS;
    memncpy(gs320200_back_buffer, vid_addr, GS320200_WIDTH*GS320200_HEIGHT);
}

u32 gs320200_get_offset(u32 x, u32 y){
    return y*GS320200_WIDTH+x;
}