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

#define MAX_GRIDS 14
#define CURSOR_COLOUR 0x7FF
#define SEA_COLOUR 0x0099
#define BG_UPPER_X 14
#define BG_LOWER_X 294
#define BG_UPPER_Y 45
#define BG_LOWER_Y 125

//void initialize_baby(Tower*, int, int, int, int , int);
void set_baby_positions(Tower* baby[]);
//void set_baby_positions(Tower baby[]);
void set_baby_attributes(Tower* baby[], int grid, int*);

void draw_bullet(alt_up_pixel_buffer_dma_dev* pixel_buffer, int x_start, int y_start, int color);

void draw_background_bullet(alt_up_pixel_buffer_dma_dev* pixel_buffer, int x_start, int y_start);

//void initialize_sharks(int, int , int, int, int , int , int );
void set_cursor(int, int);
//void draw_baby(int*, int*, int , alt_up_pixel_buffer_dma_dev*);
void draw_baby(Tower* baby, alt_up_pixel_buffer_dma_dev*);
//void draw_baby(Tower baby[] , int, alt_up_pixel_buffer_dma_dev*);

//void draw_shark(int ,int , alt_up_pixel_buffer_dma_dev* );
void draw_cursor(int*,int, alt_up_pixel_buffer_dma_dev*);

//void tower_selection(Tower*, int, alt_up_ps2_dev* , KB_CODE_TYPE , alt_u8 , char );


#endif /* GRAPHICS_H_ */
