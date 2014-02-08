#include <stdio.h>
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"

#include "title_screen.h"
#include "graphics.h"
#include "game_structs.h"
#include "tower_select.h"
#include "Colors.h"
#include "bitmaps.h"
//#include "cursor.h"
extern int baby_bmp[];
extern int infantry_bmp[];

//Function will initialize position and colour values for the baby graphics
//void initialize_baby(Tower baby, int num, int health, int bullet, int fire_rate, int grid, int colour){
void set_baby_positions(Tower* baby[]){

		int i,j;
		int grid = 0;
		// how may spaces the babies are spaced apart
		int increment = 40;

		int body_x1 = BG_LOWER_X - (0.8*increment); //269
		int body_y1 = BG_UPPER_Y + (0.2*increment);
		int body_x2 = body_x1 + 25;
		int body_y2 = body_y1 + 30;

		for(j = 0; j < NUMROW; j++){
			for(i = 0; i < (NUMTOW/NUMROW); i++){
				baby[grid] = malloc(sizeof(Tower));
				//starting at grid 1 all the way to grid 7, give the towers their permanent positions
				baby[grid]->body_pos[0] = body_x1 - ((i)*increment); //0
				baby[grid]->body_pos[1] = body_y1 + ((j)*increment) ; // 60
				baby[grid]->body_pos[2] = body_x2 - ((i)*increment); // 40
				baby[grid]->body_pos[3] = body_y2 + ((j)*increment); // 100
				baby[grid]->lane = j;
				baby[grid]->isAlive = 0;
				grid++;

			}
		}


}


void set_baby_attributes(Tower* baby[], int grid, int temp []){

	baby[grid]->colour = temp[0];
	baby[grid]->health = temp[1];
	baby[grid]->bulletType = temp[2];
	baby[grid]->toAttack = temp[3];
	baby[grid]->baseAttack = temp[3];
	baby[grid]->bulHead = NULL;





}

/*
//Function will initialize position and colour values for the shark graphics
void initialize_shark(int type, int dmg, int health, int speed, int attack, int body_pos[], int colour){

}*/

/*initializes cursor struct*/
void set_cursor(int grid, int colour){
	int x_multiplier;
	int y_multiplier;
	int increment = 40;
	int grids_per_row = (NUMTOW/NUMROW);
	int x1 = BG_UPPER_X;
	int y1 = BG_UPPER_Y;
	int x2 = BG_UPPER_X + increment;
	int y2 = BG_LOWER_Y - ((NUMROW-1)*increment);

	prev_cur.pos[0] = cur.pos[0];
	prev_cur.pos[1] = cur.pos[1];
	prev_cur.pos[2] = cur.pos[2];
	prev_cur.pos[3] = cur.pos[3];

	x_multiplier = ((grids_per_row-1)-(grid%grids_per_row));
	if(grid <= grids_per_row-1){
		y_multiplier = 0;
	}
	else if (grid <= (2*grids_per_row)-1){
		y_multiplier = 1;
	}
	else if (grid <= (3*grids_per_row)-1){
		y_multiplier = 2;
	}
	else if (grid <= (4*grids_per_row)-1){
		y_multiplier = 3;
	}

	cur.pos[0] = x1 + (x_multiplier*increment); //14
	cur.pos[1] = y1 + (y_multiplier*increment); // 45
	cur.pos[2] = x2 + (x_multiplier*increment); // 54
	cur.pos[3] = y2 + (y_multiplier*increment); // 85






	cur.colour = colour;
}

// Function will draw a baby image using info generated by the initialize function
//void draw_baby(Tower* baby[], int num, int body_pos[], int diaper_pos[], int colour, alt_up_pixel_buffer_dma_dev* pixel_buffer){
void draw_baby(Tower* baby, alt_up_pixel_buffer_dma_dev* pixel_buffer, int tower_type){

	int i,j,k;
	int pixel_el = 0;
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer));
		printf("data = %x before huge ass array \n");

	int image_to_draw[750];

	//Check which .bmp image to draw. Depends on what the tower on this grid's type is
	switch (tower_type){
	case 1:

		for(k = 0; k < 750; k++){
		image_to_draw[k] = baby_bmp[k];
		}
		break;
	case 2:

		for(k = 0; k < 750; k++){
		image_to_draw[k] = infantry_bmp[k];
		}
		break;
	}

	printf("data = %x after array \n");
	// go through the bmp array, and draw image pixel by pixel, skipping transparent pixels.
	for(i = 0; i < 30; i++)
	{
		for(j = 0; j < 25; j++){

			if(image_to_draw[pixel_el]!= BLACK){
				alt_up_pixel_buffer_dma_draw(pixel_buffer, image_to_draw[pixel_el], baby->body_pos[0]+j, baby->body_pos[1]+i);
			}
			pixel_el++;
		}

	}
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	printf("data = %x after drawing \n");




}

/*draws and updates the cursor on the screen*/
void draw_cursor(int pos[],int colour, alt_up_pixel_buffer_dma_dev* pixel_buffer){
	//alt_up_pixel_buffer_dma_draw_box(pixel_buffer, BG_UPPER_X, BG_UPPER_Y, BG_LOWER_X, BG_LOWER_Y, SEA_COLOUR, 0);

	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, prev_cur.pos[0], prev_cur.pos[1],prev_cur.pos[2], prev_cur.pos[3], SEA_COLOUR, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, pos[0], pos[1],pos[2], pos[3], colour, 0);
}

/* Draws bullet */
void draw_bullet(alt_up_pixel_buffer_dma_dev* pixel_buffer, int x_start, int y_start, int color) {
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_start, y_start, x_start + 2, y_start + 2, color, 0);
}
/* Draws bullet with background color */
void draw_background_bullet(alt_up_pixel_buffer_dma_dev* pixel_buffer, int x_start, int y_start) {
	int color_inc = 1;
	int i;
	for(i = 45; i < y_start; i++) {
		if(i%8 == 0) color_inc++;
	}
	for(i = y_start; i <= y_start + 2; i++) {
		alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, x_start, x_start+12, i, BLACK + color_inc, 0);
		if(i % 8 == 0) {
			color_inc++;
		}
	}
}

