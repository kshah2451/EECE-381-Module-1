/*
 * graphics.h
 *
 *  Created on: 2014-01-28
 *      Author: Cyril
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"
#include "game_structs.h"

#define MAX_GRIDS 16
#define CURSOR_COLOUR 0x7FF
#define SEA_COLOUR 0x0099
#define BG_UPPER_X 0
#define BG_LOWER_X 320
#define BG_UPPER_Y 60
#define BG_LOWER_Y 140

void initialize_baby(Tower*, int, int, int, int , int);
//void initialize_sharks(int, int , int, int, int , int , int );
void initialize_cursor(int, int);
//void draw_baby(int*, int*, int , alt_up_pixel_buffer_dma_dev*);
void draw_baby(Tower* , alt_up_pixel_buffer_dma_dev*);

//void draw_shark(int ,int , alt_up_pixel_buffer_dma_dev* );
void draw_cursor(int*,int, alt_up_pixel_buffer_dma_dev*);



#endif /* GRAPHICS_H_ */
