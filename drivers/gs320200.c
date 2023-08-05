#include "gs320200.h"
#include "../libc/stdlib.h"

void gs320200_draw_point(u32 x, u32 y, u32 color){
    u8* vid_address = (u8*)GS320200_ADDRESS+gs320200_get_offset(x, y);
    *(vid_address) = color;
}

void gs320200_draw_error(u32 color){
    u8* vid_address = (u8*)GS320200_ADDRESS+(GS320200_HEIGHT-GS320200_ERROR_BOX_SIZE+1)*GS320200_WIDTH-GS320200_ERROR_BOX_SIZE;
    for(int i = 0; i < GS320200_ERROR_BOX_SIZE; ++i){
        memset(vid_address+i*GS320200_WIDTH, color, GS320200_ERROR_BOX_SIZE);
    }
}

u32 gs320200_get_offset(u32 x, u32 y){
    return y*GS320200_WIDTH+x;
}