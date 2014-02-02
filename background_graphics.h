#ifndef BACKGROUND_GRAPHICS_H_
#define BACKGROUND_GRAPHICS_H

#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "Colors.h"
#include "graphics.h"

void draw_sky(alt_up_pixel_buffer_dma_dev*);

void draw_ocean(alt_up_pixel_buffer_dma_dev*);

void draw_boardwalk(alt_up_pixel_buffer_dma_dev*);

void draw_grids(alt_up_pixel_buffer_dma_dev*);

void draw_sharkfin(alt_up_pixel_buffer_dma_dev * pixel_buffer, int x_start, int y_start, int color);


#endif


