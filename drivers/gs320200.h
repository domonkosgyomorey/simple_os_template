#ifndef GS320200_H
#define GS320200_H

#include "../hdep/types.h"

#define GS320200_ADDRESS            0xA0000
#define GS320200_HEIGHT             200
#define GS320200_WIDTH              320
#define GS320200_SIZE               64000
#define GS320200_ERROR_BOX_SIZE     40

#define GS320200_BLACK              0
#define GS320200_BLUE               1
#define GS320200_GREEN              2
#define GS320200_CYAN               3
#define GS320200_RED                4
#define GS320200_MAGENTA            5
#define GS320200_BROWN              6
#define GS320200_LIGHT_GHRAY        7
#define GS320200_DARK_GRAY          8
#define GS320200_LIGHT_BLUE         9
#define GS320200_LIGHT_GREEN        10
#define GS320200_LIGHT_CYAN         11
#define GS320200_LIGHT_RED          12
#define GS320200_LIGHT_MAGENTA      13
#define GS320200_YELLOW             14
#define GS320200_WHITE              15

void gs320200_draw_point(u32 x, u32 y, u8 color);
void gs320200_draw_error(u32 color);
void gs320200_draw_rect(u32 x, u32 y, u32 width, u32 height, u8 color);
void gs320200_swap_buffers();
u32 gs320200_get_offset(u32 x, u32 y);


#endif // GS320240_H
