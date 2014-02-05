#include <stdio.h>
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"

#include "title_screen.h"
#include "graphics.h"
#include "game_structs.h"
#include "tower_select.h"
#include "Colors.h"
//#include "cursor.h"



//Function will initialize position and colour values for the baby graphics
//void initialize_baby(Tower baby, int num, int health, int bullet, int fire_rate, int grid, int colour){
void set_baby_positions(Tower* baby[]){

		int i;


		int body_x1 = 269;
		int body_y1 = 60;
		int body_x2 = 279;
		int body_y2 = 65;

		// how may spaces the babies are spaced apart
		int increment = 40;


		// set tower positions for lane 0
		for(i = 0; i<(MAX_GRIDS/2); i++){
			baby[i] = malloc(sizeof(Tower));
			//starting at grid 1 all the way to grid 7, give the towers their permanent positions
			baby[i]->body_pos[0] = body_x1 - ((i)*increment); //0
			baby[i]->body_pos[1] = body_y1 ; // 60
			baby[i]->body_pos[2] = body_x2 - ((i)*increment); // 40
			baby[i]->body_pos[3] = body_y2 ; // 100
			baby[i]->lane = 0;
			baby[i]->isAlive = 0;
			baby[i]->bulHead = NULL;

		}

		// set tower positions for lane 1
		for(i = (MAX_GRIDS/2); i<MAX_GRIDS; i++){
			//starting at grid 8 all the way to grid 14, give the towers their permanent positions
			baby[i] = malloc(sizeof(Tower));

			baby[i]->body_pos[0] = body_x1 - ((i%((MAX_GRIDS/2)))*increment);
			baby[i]->body_pos[1] = body_y1 + increment;
			baby[i]->body_pos[2] = body_x2 - ((i%((MAX_GRIDS/2)))*increment);
			baby[i]->body_pos[3] = body_y2 + increment;
			baby[i]->lane = 1;
			baby[i]->isAlive = 0;
			baby[i]->bulHead = NULL;

		}


}


void set_baby_attributes(Tower* baby[], int grid, int temp []){

	baby[grid]->colour = temp[0];
	baby[grid]->health = temp[1];
	baby[grid]->bulletType = temp[2];
	baby[grid]->toAttack = temp[3];
	baby[grid]->baseAttack = temp[3];



}

/*
//Function will initialize position and colour values for the shark graphics
void initialize_shark(int type, int dmg, int health, int speed, int attack, int body_pos[], int colour){

}*/

/*initializes cursor struct*/
void set_cursor(int grid, int colour){

	int x1 = BG_UPPER_X;
	int y1 = BG_UPPER_Y;
	int x2 = BG_UPPER_X + (BG_LOWER_X - BG_UPPER_X)/(MAX_GRIDS/2);
	int y2 = BG_LOWER_Y - ((BG_LOWER_Y - BG_UPPER_Y)/2);
	int increment = ((BG_LOWER_Y - BG_UPPER_Y)/2);
	prev_cur.pos[0] = cur.pos[0];
	prev_cur.pos[1] = cur.pos[1];
	prev_cur.pos[2] = cur.pos[2];
	prev_cur.pos[3] = cur.pos[3];
	switch(grid){
		case 6:
			cur.pos[0] = x1; //0
			cur.pos[1] = y1; // 60
			cur.pos[2] = x2; // 40
			cur.pos[3] = y2; // 100
			break;

		case 5:
			cur.pos[0] = x1 + increment;
			cur.pos[1] = y1;
			cur.pos[2] = x2 + increment;
			cur.pos[3] = y2;
			break;
		case 4:
			cur.pos[0] = x1 + 2*increment;
			cur.pos[1] = y1;
			cur.pos[2] = x2 + 2*increment;
			cur.pos[3] = y2;
			break;
		case 3:
			cur.pos[0] = x1 + 3*increment;
			cur.pos[1] = y1;
			cur.pos[2] = x2 + 3*increment;
			cur.pos[3] = y2;
			break;
		case 2:
			cur.pos[0] = x1 + 4*increment;
			cur.pos[1] = y1;
			cur.pos[2] = x2 + 4*increment;
			cur.pos[3] = y2;
			break;
		case 1:
			cur.pos[0] = x1 + 5 * increment;
			cur.pos[1] = y1;
			cur.pos[2] = x2 + 5*increment;
			cur.pos[3] = y2;
			break;
		case 0:
			cur.pos[0] = x1 + 6*increment;
			cur.pos[1] = y1;
			cur.pos[2] = x2 + 6*increment;
			cur.pos[3] = y2;
			break;

		case 13:
			cur.pos[0] = x1;
			cur.pos[1] = y1 + increment;
			cur.pos[2] = x2;
			cur.pos[3] = y2 + increment;
			break;
		case 12:
			cur.pos[0] = x1 + increment;
			cur.pos[1] = y1 + increment;
			cur.pos[2] = x2 + increment;
			cur.pos[3] = y2 + increment;
			break;
		case 11:
			cur.pos[0] = x1 + 2*increment;
			cur.pos[1] = y1 + increment;
			cur.pos[2] = x2 + 2*increment;
			cur.pos[3] = y2 + increment;
			break;
		case 10:
			cur.pos[0] = x1 + 3*increment;
			cur.pos[1] = y1 + increment;
			cur.pos[2] = x2 + 3*increment;
			cur.pos[3] = y2 + increment;
			break;
		case 9:
			cur.pos[0] = x1 + 4*increment;
			cur.pos[1] = y1 + increment;
			cur.pos[2] = x2 + 4*increment;
			cur.pos[3] = y2 + increment;
			break;
		case 8:
			cur.pos[0] = x1 + 5*increment;
			cur.pos[1] = y1 + increment;
			cur.pos[2] = x2 + 5*increment;
			cur.pos[3] = y2 + increment;
			break;

		case 7:
			cur.pos[0] = x1 + 6*increment;
			cur.pos[1] = y1 + increment;
			cur.pos[2] = x2 + 6*increment;
			cur.pos[3] = y2 + increment;
			break;

	}

	cur.colour = colour;
}

// Function will draw a baby image using info generated by the initialize function
//void draw_baby(Tower* baby[], int num, int body_pos[], int diaper_pos[], int colour, alt_up_pixel_buffer_dma_dev* pixel_buffer){
void draw_baby(Tower* baby, alt_up_pixel_buffer_dma_dev* pixel_buffer){

	//draws baby's body
	//alt_up_pixel_buffer_dma_draw_box(pixel_buffer, baby[num].body_pos[0], baby[num].body_pos[1], baby[num].body_pos[2], baby[num].body_pos[3], baby[num].colour, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, baby->body_pos[0], baby->body_pos[1], baby->body_pos[2], baby->body_pos[3], baby->colour, 0);
	//alt_up_pixel_buffer_dma_draw_box(pixel_buffer, baby[num].diaper_pos[0], baby[num].diaper_pos[1], baby[num].diaper_pos[2], baby[num].diaper_pos[3], 0xFFFF, 0);

}
/*
// Function will draw a baby image using info generated by the initialize function
void draw_sharks(int body_pos[], int colour, alt_up_pixel_buffer_dma_dev* pixel_buffer){
        //draws shark's body
        alt_up_pixel_buffer_dma_draw_box(pixel_buffer, body_pos[0], body_pos[1], body_pos[2], body_pos[3], colour, 0);

}

*/

/*draws and updates the cursor on the screen*/
void draw_cursor(int pos[],int colour, alt_up_pixel_buffer_dma_dev* pixel_buffer){
	//alt_up_pixel_buffer_dma_draw_box(pixel_buffer, BG_UPPER_X, BG_UPPER_Y, BG_LOWER_X, BG_LOWER_Y, SEA_COLOUR, 0);
	printf("ABefore Cursor\n");

	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, prev_cur.pos[0], prev_cur.pos[1],prev_cur.pos[2], prev_cur.pos[3], SEA_COLOUR, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, pos[0], pos[1],pos[2], pos[3], colour, 0);
	printf("After CurosrASDAKSDASD\n");
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

