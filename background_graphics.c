#include <stdio.h>
#include "background_graphics.h"
#include "bitmaps.h"

//extern short int jellyfish[];
extern alt_up_pixel_buffer_dma_dev* pixel_buffer;
//extern short int shark_bmp[];

extern int levelThreeFlag;

/* Draws sky with sun background */
void draw_sky(alt_up_pixel_buffer_dma_dev* pixel_buffer){
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer,21,0,320,39,0xAF7F,0);
}

void draw_boardwalk(alt_up_pixel_buffer_dma_dev* pixel_buffer) {
	int pixel_el = 0;
	int i, j;

	for(i = 0; i < 240; i++) {
		for(j = 0; j < 21; j++) {
			if(dock_bmp[pixel_el] == 0x4E99) {
				alt_up_pixel_buffer_dma_draw_box(pixel_buffer,j, i, j, i, 0x4dba, 0);
			}
			else {
				alt_up_pixel_buffer_dma_draw_box(pixel_buffer, j, i, j, i, dock_bmp[pixel_el], 0);
			}
			pixel_el++;
		}
	}
}

/* Draws ocean and planks background */
void draw_ocean(alt_up_pixel_buffer_dma_dev* pixel_buffer){
	alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 21, 320, 40, 0x2CD6, 0);
	alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 21, 320, 41, 0x2CD6, 0);
	alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 21, 320, 42, 0x34F6, 0);
	alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 21, 320, 43, 0x34F6, 0);
	alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 21, 320, 44, 0x3D17, 0);
	alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 21, 320, 45, 0x3d17, 0);
	alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 21, 320, 46, 0x3d38, 0);
	alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 21, 320, 47, 0x3d38, 0);
	alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 21, 320, 48, 0x4578, 0);
	alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 21, 320, 49, 0x4578, 0);
	alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 21, 320, 50, 0x4599, 0);
	alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 21, 320, 51, 0x4599, 0);
	alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 21, 320, 52, 0x4dba, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 21, 53, 320, 240, 0x4dba, 0);
}





void draw_sharkfin(alt_up_pixel_buffer_dma_dev * pixel_buffer, int x_start, int y_start, int color) {

	int c = 1;
	int y;
	int i,j;
	int pixel_el = 0;
	int col_swap = 0;
/*	for(y = y_start; y < y_start + 24; y++) {
		alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, x_start, x_start + c , y, color , 0);
		x_start--;
		c++;
	}*/

	switch (color){

	case 0x7bef:
		col_swap = 0x532F;
		break;
	case 0xffff:
		col_swap = 0xffff;
		break;
	case 0x0000:
		col_swap = 0x0000;
		break;
	case 0x00ff:
		col_swap= 0x00ff;
		break;
	case 0x0ff0:
		col_swap = 0x0ff0;
		break;
	}


	for(i = y_start; i < y_start+30; i++)
	{

		for(j = x_start; j < x_start+25; j++){


			if(shark_bmp[pixel_el]!= 0x2589){

				if(levelThreeFlag == 0){
					if(shark_bmp[pixel_el] == 0x532F){
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer, j, i, j, i, col_swap, 0);
					}
					else{
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer, j, i, j, i, shark_bmp[pixel_el], 0);

					}
				}
				else if(levelThreeFlag == 1){
					if(x_start < (FOG)){
						if(shark_bmp[pixel_el] == 0x532F){
							alt_up_pixel_buffer_dma_draw_box(pixel_buffer, j, i, j, i, col_swap, 0);
						}
						else{
							alt_up_pixel_buffer_dma_draw_box(pixel_buffer, j, i, j, i, shark_bmp[pixel_el], 0);

						}
					}
				}
			}

			pixel_el++;

		}

	}





}

void draw_background_sharkfin(alt_up_pixel_buffer_dma_dev * pixel_buffer, int x_start, int y_start) {
	int i, j;
	int pos = 0;
	for(i = 0; i < 30; i++) {
		for(j = 0; j < 25; j++) {
			if(shark_bmp[pos] != 0x2589) {
				alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_start + j, y_start + i, x_start + j, y_start + i, 0x4dba, 0);
			}
			pos++;
		}
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


void set_jellyfish(){
	int i,j;
	int jelly_count = 0;
	int increment = 40;
	int jelly_per_row = 2;
	int x1 = BG_UPPER_X;
	int y1 = BG_UPPER_Y;
	int x2 = BG_UPPER_X + increment;
	int y2 = BG_LOWER_Y - ((NUMROW-1)*increment);

	for(i = 0; i < (NUMTOW/NUMROW); i++){
		for(j = 0; j < NUMROW; j++){
			if((j%2)==0){
				if(((i%7)== JELLYGRID1 || (i%7) == JELLYGRID2)){
					//draw jelly
					draw_jellyfish(x1 + (i*increment),y1 +(j*increment));

					jelly_count++;
				}
			}
		else if ((j%2)==1){
				if(((i%7)== JELLYGRID3 || (i%7) == JELLYGRID4)){
					//draw jelly
					draw_jellyfish(x1 + (i*increment) ,y1 + (j*increment));
					jelly_count++;
				}
			}
		}
	}

}


void draw_jellyfish(int jelly_x, int jelly_y){

	int i = jelly_x;
	int j = jelly_y;
	int pixel_el = 0;
	for(i = jelly_x; i < jelly_x+40; i++)
		{
			for(j = jelly_y; j < jelly_y+40; j++){

				if(jellyfish[pixel_el]!= 0x051D){
					alt_up_pixel_buffer_dma_draw_box(pixel_buffer, i, j, i+1, j+1, jellyfish[pixel_el], 0);

				}

				pixel_el++;
			}

		}
}
