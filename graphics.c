#include <stdio.h>
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"

#include "game_structs.h"
#include "graphics.h"
#include "cursor.h"



//initialize functions may be placed in another file as they are not strictly VGA related
//Function will initialize position and colour values for the baby graphics
void initialize_baby(int health, int bullet, int fire_rate, int body_pos[], int colour){

}

//Function will initialize position and colour values for the shark graphics
void initialize_shark(int type, int dmg, int health, int speed, int attack, int body_pos[], int colour){

}

//Function will initialize position and colour values for the cursor graphics
/*initializes cursor struct*/
initialize_cursor(int grid, int colour){

	int x1 = BG_UPPER_X; 
	int y1 = BG_UPPER_Y; 
	int x2 = (BG_LOWER_X - BG_UPPER_X)/(MAX_GRIDS/2);
	int y2 = BG_LOWER_Y - ((BG_LOWER_Y - BG_UPPER_Y)/2);
	int increment = ((BG_LOWER_Y - BG_UPPER_Y)/2);
	
	/*Check what grid the cursor is on, and assign new coordinates accordingly*/
	switch(grid){
		case 1:
			cur.pos[0] = x1; //0
			cur.pos[1] = y1; // 60
			cur.pos[2] = x2; // 40
			cur.pos[3] = y2; // 100
			break;

		case 2:
			cur.pos[0] = x1 + increment;
			cur.pos[1] = y1;
			cur.pos[2] = x2 + increment;
			cur.pos[3] = y2;
			break;
		case 3:
			cur.pos[0] = x1 + 2*increment;
			cur.pos[1] = y1;
			cur.pos[2] = x2 + 2*increment;
			cur.pos[3] = y2;
			break;
		case 4:
			cur.pos[0] = x1 + 3*increment;
			cur.pos[1] = y1;
			cur.pos[2] = x2 + 3*increment;
			cur.pos[3] = y2;
			break;
		case 5:
			cur.pos[0] = x1 + 4*increment;
			cur.pos[1] = y1;
			cur.pos[2] = x2 + 4*increment;
			cur.pos[3] = y2;
			break;
		case 6:
			cur.pos[0] = x1 + 5 * increment;
			cur.pos[1] = y1;
			cur.pos[2] = x2 + 5*increment;
			cur.pos[3] = y2;
			break;
		case 7:
			cur.pos[0] = x1 + 6*increment;
			cur.pos[1] = y1;
			cur.pos[2] = x2 + 6*increment;
			cur.pos[3] = y2;
			break;
		case 8:
			cur.pos[0] = x1 + 7*increment;
			cur.pos[1] = y1;
			cur.pos[2] = x2 + 7*increment;
			cur.pos[3] = y2;
			break;
		case 9:
			cur.pos[0] = x1;
			cur.pos[1] = y1 + increment;
			cur.pos[2] = x2;
			cur.pos[3] = y2 + increment;
			break;
		case 10:
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
		case 12:
			cur.pos[0] = x1 + 3*increment;
			cur.pos[1] = y1 + increment;
			cur.pos[2] = x2 + 3*increment;
			cur.pos[3] = y2 + increment;
			break;
		case 13:
			cur.pos[0] = x1 + 4*increment;
			cur.pos[1] = y1 + increment;
			cur.pos[2] = x2 + 4*increment;
			cur.pos[3] = y2 + increment;
			break;
		case 14:
			cur.pos[0] = x1 + 5*increment;
			cur.pos[1] = y1 + increment;
			cur.pos[2] = x2 + 5*increment;
			cur.pos[3] = y2 + increment;
			break;

		case 15:
			cur.pos[0] = x1 + 6*increment;
			cur.pos[1] = y1 + increment;
			cur.pos[2] = x2 + 6*increment;
			cur.pos[3] = y2 + increment;
			break;

		case 16:
			cur.pos[0] = x1 + 7*increment;
			cur.pos[1] = y1 + increment;
			cur.pos[2] = x2 + 7*increment;
			cur.pos[3] = y2 + increment;
			break;

	}

	cur.colour = colour;
}

// Function will draw a baby image using info generated by the initialize function
void draw_baby(int body_pos[], int colour, alt_up_pixel_buffer_dma_dev* pixel_buffer){
	//draws baby's body
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, body_pos[0], body_pos[1], body_pos[2], body_pos[3], colour, 0);

}

// Function will draw a baby image using info generated by the initialize function

void draw_sharks(int body_pos[], int colour, alt_up_pixel_buffer_dma_dev* pixel_buffer){
	//draws shark's body
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, body_pos[0], body_pos[1], body_pos[2], body_pos[3], colour, 0);

}

/*draws and updates the cursor on the screen*/
draw_cursor(int pos[],int colour, alt_up_pixel_buffer_dma_dev* pixel_buffer){
	/*redraw background image*/
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, BG_UPPER_X, BG_UPPER_Y, BG_LOWER_X, BG_LOWER_Y, SEA_COLOUR, 0);
	/*draw image*/
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, pos[0], pos[1],pos[2], pos[3], colour, 0);

}
