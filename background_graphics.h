#ifndef BACKGROUND_GRAPHICS_H_
#define BACKGROUND_GRAPHICS_H

#include "altera_up_avalon_video_pixel_buffer_dma.h"

#define BLACK 0x0000
#define WHITE 0xFFFF
#define RED 0xF800
#define D_BLUE 0x1B
#define L_BLUE 0xDFF
#define BLUE 0x1F
#define GREEN 0x7E0
#define YELLOW 0xFFE0
#define BROWN 0x7FE0
#define ORANGE 0xFBE0

void draw_sky(alt_up_pixel_buffer_dma_dev*);

void draw_ocean(alt_up_pixel_buffer_dma_dev*);

void draw_grids(alt_up_pixel_buffer_dma_dev*);


#endif


