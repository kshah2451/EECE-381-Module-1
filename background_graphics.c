#include <stdio.h>
#include "background_graphics.h"

/* Draws sky with sun background */
void draw_sky(alt_up_pixel_buffer_dma_dev* pixel_buffer){
	int color_inc = 0x0001;
	int x0_pos = 0;
	int x1_pos = 320;
	int change = 4;
	int y_pos;


	// Draws sky
	for(y_pos = 0; y_pos < 45; y_pos++) {
		alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, x0_pos, x1_pos, y_pos, 0xF800 + color_inc, 0);
		if(y_pos % 3 == 0) color_inc++;
	}

	x0_pos = 155;
	x1_pos = 165;
	// Draws sun
	for(y_pos = 37; y_pos < 45; y_pos++) {
		alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, x0_pos, x1_pos, y_pos, ORANGE, 0);
		if(y_pos == 37 || y_pos == 39) change = 4;
		else if(y_pos == 38) change = 3;
		else change = 1;
		x0_pos -= change; x1_pos += change;
	}
}

void draw_boardwalk(alt_up_pixel_buffer_dma_dev* pixel_buffer) {
	int i;
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 45, 14, 240, 0x79E5, 0);
	for(i = 45; i < 240; i+=4 ) {
		alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 0, 14, i, BLACK, 0);
	}
}

/* Draws ocean and planks background */
void draw_ocean(alt_up_pixel_buffer_dma_dev* pixel_buffer){
	int i;
	int color_inc = 0x0001;

	// Draws planks
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 45, 14, 240, 0x79E5, 0);
	for(i = 45; i < 240; i+=4 ) {
		alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 0, 14, i, BLACK, 0);
	}

	// Draws ocean
	for(i = 45; i < 240; i++) {
		alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 14, 320, i, BLACK + color_inc, 0);
		if(i == 85) {
			printf("Y = %i COLOR_inc = %X\n", i, color_inc);
		}
		if(i % 8 == 0) {
			//printf("%X\n", BLACK + color_inc);
			color_inc++;
		}

	}






}
void draw_sharkfin(alt_up_pixel_buffer_dma_dev * pixel_buffer, int x_start, int y_start, int color) {
	int c = 1;
	int y;
	for(y = y_start; y < y_start + 24; y++) {
		alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, x_start, x_start + c , y, color , 0);
		x_start--;
		c++;
	}
}

void draw_background_sharkfin(alt_up_pixel_buffer_dma_dev * pixel_buffer, int x_start, int y_start) {
	int y;
	int c = 1;
	int color_inc = 0x0001;
	switch(y_start) {
	case (BG_UPPER_Y):
		for(y = y_start; y < y_start + 24; y++) {
			alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, x_start, x_start + c, y, BLACK + color_inc, 0);
			x_start--;
			c++;
			if(y % 8 == 0) {
				color_inc++;
			}
		}
		break;
	case (BG_UPPER_Y + 40):
		color_inc = 6;
		for(y = y_start; y < y_start + 24; y++) {
			alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, x_start, x_start + c, y, BLACK + color_inc, 0);
			x_start--;
			c++;
			if(y % 8 == 0) {
				color_inc++;
			}
		}
		break;

	case (BG_UPPER_Y + 80):
		color_inc = 10;
		for(y = y_start; y < y_start + 24; y++) {
			alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, x_start, x_start + c, y, BLACK + color_inc, 0);
			x_start--;
			c++;
			if(y % 8 == 0) {
				color_inc++;
			}
		}
		break;

	case (BG_UPPER_Y + 120):
		color_inc = 16;
		for(y = y_start; y < y_start + 24; y++) {
			alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, x_start, x_start + c, y, BLACK + color_inc, 0);
			x_start--;
			c++;
			if(y % 8 == 0) {
				color_inc++;
			}
		}
		break;

	}







}

/* Draws grids for tower placement */

void draw_grids(alt_up_pixel_buffer_dma_dev* pixel_buffer){
	int i,j;
	int increment = 40;
	int x1 = BG_UPPER_X;
	int y1 = BG_UPPER_Y;
	int x2 = BG_UPPER_X + increment;
	int y2 = BG_LOWER_Y - ((NUMROW-1)*increment);

	for(i = 0; i < (NUMTOW/NUMROW); i++){
		for(j = 0; j < NUMROW; j++){
			alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, x1 + (i* increment), y1+(j*increment),x2+ (i* increment), y2+(j*increment), SEA_COLOUR, 0);
		}
	}



}
