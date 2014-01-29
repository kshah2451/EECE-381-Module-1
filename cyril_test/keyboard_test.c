/*
 * "Hello World" example.
 *
 * This example prints 'Hello from Nios II' to the STDOUT stream. It runs on
 * the Nios II 'standard', 'full_featured', 'fast', and 'low_cost' example
 * designs. It runs with or without the MicroC/OS-II RTOS and requires a STDOUT
 * device in your system's hardware.
 * The memory footprint of this hosted application is ~69 kbytes by default
 * using the standard reference design.
 *
 * For a reduced footprint version of this template, and an explanation of how
 * to reduce the memory footprint for a given application, see the
 * "small_hello_world" template.
 *
 */

/*Add to game_structs.h*/
typedef struct
{
	int pos[4];		// where it is in the grid
	int state;		// on or off
	int colour;

} Cursor;
Cursor cur;


/* Tower/Babies Struct*/
typedef struct
{
	int health;
	int bullet;
	int fire_rate;
	// Position of Tower's body (assuming tower is just a rectangle)
	//right x-coordinate = position[0], right y-coordinate = pos[1],
	//left x-coordinate = pos[2], left y-coordinate = pos[3]
	int body_pos[4];
	int diaper_pos[4];
	// vga info like the boxes that make up the image and colour
	int colour;


}Tower;
Tower baby;




#include <stdio.h>
#include "altera_up_ps2_keyboard.h"
#include "altera_up_avalon_ps2.h"
#include "altera_up_avalon_ps2_regs.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"

#define MAX_GRIDS 16
#define CURSOR_COLOUR 0x7FF
#define SEA_COLOUR 0x0099
#define BG_UPPER_X 0
#define BG_LOWER_X 320
#define BG_UPPER_Y 60
#define BG_LOWER_Y 140

#define PS2_NAME "/dev/ps2"
#define PS2_TYPE "altera_up_avalon_ps2"
#define PS2_BASE 0x00004030
#define PS2_SPAN 8
#define PS2_IRQ 0
#define PS2_HDL_PARAMETERS ""
#define ALT_MODULE_CLASS_ps2 altera_up_avalon_ps2

void initialize_cursor(int, int);
void draw_cursor(int*,int, alt_up_pixel_buffer_dma_dev*);
void title_screen(alt_up_pixel_buffer_dma_dev*,alt_up_char_buffer_dev *, int, alt_up_ps2_dev *, KB_CODE_TYPE,alt_u8, char );

void initialize_baby(int, int, int, int , int);
void draw_baby(int*, int*, int , alt_up_pixel_buffer_dma_dev*);



/*main gameplay cursor logic, with some title screen features .. will have to seperate*/
int main()
{
	KB_CODE_TYPE decode_mode;
	alt_u8 data;
	char ascii;
	char *p;
	int start = 0;



	int grid_pos = 1;

	alt_up_ps2_dev *ps2_kb;
	ps2_kb=alt_up_ps2_open_dev("/dev/ps2");
	alt_up_ps2_init(ps2_kb);
	alt_up_ps2_clear_fifo(ps2_kb);

	alt_up_pixel_buffer_dma_dev* pixel_buffer;
	pixel_buffer =
	  alt_up_pixel_buffer_dma_open_dev("/dev/pixel_buffer_dma");

	// Set the background buffer address – Although we don’t use the
	//background, // they only provide a function to change the background
	//buffer address, so
	// we must set that, and then swap it to the foreground.
	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer,
	PIXEL_BUFFER_BASE);

	// Swap background and foreground buffers
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);

	// Wait for the swap to complete
	while
	(alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer));

	// Initialize the character buffer
	alt_up_char_buffer_dev *char_buffer;
	char_buffer = alt_up_char_buffer_open_dev("/dev/char_drawer");
	alt_up_char_buffer_init(char_buffer);

	//clear pixel buffer memory
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);


	title_screen(pixel_buffer, char_buffer, start, ps2_kb, decode_mode, data, ascii);


	//set background image
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, BG_UPPER_X, BG_UPPER_Y, BG_LOWER_X, BG_LOWER_Y, SEA_COLOUR, 0);

	initialize_cursor(grid_pos, CURSOR_COLOUR);
	draw_cursor(cur.pos,cur.colour, pixel_buffer);

	while(1)
	 {
		if (decode_scancode(ps2_kb, &decode_mode, &data, &ascii)==0)
		{

			if(data == 0x1c){
				/*alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 60, 320, 120, 0x0099, 0);
				alt_up_pixel_buffer_dma_draw_box(pixel_buffer, pos[0], pos[1],pos[2], pos[3], colour, 0);*/
				initialize_baby(100, 1, 50, grid_pos , 0xFE99);
				draw_baby(baby.body_pos, baby.diaper_pos, baby.colour, pixel_buffer);
			}
			if(cur.pos[0] == BG_UPPER_X && cur.pos[1] == BG_UPPER_Y){
				//can't go left or up
				if(data == 0x72){ //down
					grid_pos = (MAX_GRIDS/2)+grid_pos;
					initialize_cursor(grid_pos, CURSOR_COLOUR);

					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

				}
				else if(data == 0x74){ //right
					grid_pos = grid_pos + 1;
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

				}
			}

			else if(cur.pos[1] == BG_UPPER_Y && cur.pos[2] == BG_LOWER_X){
				//can't go right or up
				if(data == 0x72){ //down
					grid_pos = (MAX_GRIDS/2)+grid_pos;
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

				}
				else if(data == 0x6b){ //left
					grid_pos = grid_pos - 1;
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

				}


			}
			else if(cur.pos[3] == BG_LOWER_Y && cur.pos[2] == BG_LOWER_X){
				//can't go down or right
				if(data == 0x75){ //up
					grid_pos = grid_pos - (MAX_GRIDS/2);
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);
				}

				else if(data == 0x6b){ //left
					grid_pos = grid_pos - 1;
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

				}


			}


			else if(cur.pos[0] == BG_UPPER_X && cur.pos[3] == BG_LOWER_Y){
				//can't go left or down

				if(data == 0x75){ //up
					grid_pos = grid_pos - (MAX_GRIDS/2);
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);
				}
				else if(data == 0x74){ //right
					grid_pos = grid_pos + 1;
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

				}


			}

			else if(cur.pos[1] == BG_UPPER_Y){
				//can't go up
				if(data == 0x72){ //down
					grid_pos = (MAX_GRIDS/2)+grid_pos;
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

				}
				else if(data == 0x74){ //right
					grid_pos = grid_pos + 1;
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

				}
				else if(data == 0x6b){ //left
					grid_pos = grid_pos - 1;
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

				}


			}



			else if(cur.pos[3] == BG_LOWER_Y){
				//can't go down
				if(data == 0x75)
				{ //up
					grid_pos = grid_pos - (MAX_GRIDS/2);
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);
				}
				else if(data == 0x74){ //right
					grid_pos = grid_pos + 1;
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

				}
				else if(data == 0x6b){ //left
					grid_pos = grid_pos - 1;
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

				}


			}


			}

		 }


  return 0;
}

/*initializes cursor struct*/
initialize_cursor(int grid, int colour){

	int x1 = BG_UPPER_X;
	int y1 = BG_UPPER_Y;
	int x2 = (BG_LOWER_X - BG_UPPER_X)/(MAX_GRIDS/2);
	int y2 = BG_LOWER_Y - ((BG_LOWER_Y - BG_UPPER_Y)/2);
	int increment = ((BG_LOWER_Y - BG_UPPER_Y)/2);

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

//Function will initialize position and colour values for the baby graphics
void initialize_baby(int health, int bullet, int fire_rate, int grid, int colour){

		//Baby's body
		int body_x1 = 15;
		int body_y1 = 75;
		int body_x2 = 25;
		int body_y2 = 85;

		//Baby's diapers
		int diaper_x1 = 15;
		int diaper_y1 = 82;
		int diaper_x2 = 25;
		int diaper_y2 = 85;


		int increment = 40;

		switch(grid){
			case 1:
				baby.body_pos[0] = body_x1; //0
				baby.body_pos[1] = body_y1; // 60
				baby.body_pos[2] = body_x2; // 40
				baby.body_pos[3] = body_y2; // 100

				baby.diaper_pos[0] = diaper_x1; //0
				baby.diaper_pos[1] = diaper_y1; // 60
				baby.diaper_pos[2] = diaper_x2; // 40
				baby.diaper_pos[3] = diaper_y2; // 100

				break;

			case 2:
				baby.body_pos[0] = body_x1 + increment; //0
				baby.body_pos[1] = body_y1; // 60
				baby.body_pos[2] = body_x2 + increment; // 40
				baby.body_pos[3] = body_y2; // 100

				baby.diaper_pos[0] = diaper_x1 + increment;
				baby.diaper_pos[1] = diaper_y1;
				baby.diaper_pos[2] = diaper_x2 + increment;
				baby.diaper_pos[3] = diaper_y2;
				break;
			case 3:
				baby.body_pos[0] = body_x1 + 2*increment;
				baby.body_pos[1] = body_y1; // 60
				baby.body_pos[2] = body_x2+ 2*increment;
				baby.body_pos[3] = body_y2; // 100

				baby.diaper_pos[0] = diaper_x1 + 2*increment;
				baby.diaper_pos[1] = diaper_y1;
				baby.diaper_pos[2] = diaper_x2 + 2*increment;
				baby.diaper_pos[3] = diaper_y2;
				break;
			case 4:
				baby.body_pos[0] = body_x1+ 3*increment;
				baby.body_pos[1] = body_y1; // 60
				baby.body_pos[2] = body_x2+ 3*increment;
				baby.body_pos[3] = body_y2; // 100

				baby.diaper_pos[0] = diaper_x1 + 3*increment;
				baby.diaper_pos[1] = diaper_y1;
				baby.diaper_pos[2] = diaper_x2 + 3*increment;
				baby.diaper_pos[3] = diaper_y2;
				break;

		}
		baby.health = health;
		baby.fire_rate = fire_rate;
		baby.bullet = bullet;
		baby.colour = colour;


}






/*draws and updates the cursor on the screen*/
void draw_cursor(int pos[],int colour, alt_up_pixel_buffer_dma_dev* pixel_buffer){
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, BG_UPPER_X, BG_UPPER_Y, BG_LOWER_X, BG_LOWER_Y, SEA_COLOUR, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, pos[0], pos[1],pos[2], pos[3], colour, 0);

}

// Function will draw a baby image using info generated by the initialize function
void draw_baby(int body_pos[], int diaper_pos[], int colour, alt_up_pixel_buffer_dma_dev* pixel_buffer){
	//draws baby's body
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, body_pos[0], body_pos[1], body_pos[2], body_pos[3], colour, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, diaper_pos[0], diaper_pos[1], diaper_pos[2], diaper_pos[3], 0xFFFF, 0);

}




/*Title Screen code*/
void title_screen(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev * char_buffer, int start, alt_up_ps2_dev * ps2_kb, KB_CODE_TYPE decode_mode,alt_u8 data, char ascii)

//ps2_kb, &decode_mode, &data, &ascii
{
	int j,k;
	//alt_up_pixel_buffer_dma_dev* pixel_buffer;
	alt_up_char_buffer_clear(char_buffer);
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);



	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 60, 320, 120, 0x0099, 0);

	//Baby
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 100, 80, 115, 110, 0xFE99, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 95, 90, 120, 110, 0xFE99, 0);

	//Eyes
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 104, 82, 106, 84, 0x0000, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 110, 82, 112, 84, 0x0000, 0);


	//Arms
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 90, 92, 100, 100, 0xFE99, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 115, 92, 125, 100, 0xFE99, 0);

	//Gun
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 122, 92, 124, 98, 0xCEFD, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 125, 92, 132, 94, 0xCEFD, 0);
	// Diapers
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 95, 102, 120, 110, 0xAFFF, 0);

	//Legs
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 90, 106, 100, 114, 0xFE99, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 115, 106, 125, 114, 0xFE99, 0);

	/**Shark Image**/
	//Dorsal Fin
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 198, 66, 202, 68, 0xCEFD, 0); //0xFFFA
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 193, 68, 207, 73, 0xCEFD, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 190, 73, 210, 80, 0xCEFD, 0);

	//Body
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 175, 80, 240, 95, 0xCEFD, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 175, 94, 240, 105, 0xFFFF, 0);
	//alt_up_pixel_buffer_dma_draw(pixel_buffer, 0xC000, 160, 120);

	//Head
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 160, 84, 176, 99, 0xCEFD, 0);


	//Pectoral Fin
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 180, 104, 188, 109, 0xCEFD, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 184, 109, 190, 114, 0xCEFD, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 188, 114, 192, 115, 0xCEFD, 0);

	// Tail
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 240, 86, 250, 97, 0xCEFD, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 250, 88, 255, 95, 0xCEFD, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 255, 80, 265, 90, 0xCEFD, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 255, 95, 265, 105, 0xCEFD, 0);
	/****/

	// Clear the screen
	//alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);

	// Write some text
	alt_up_char_buffer_string(char_buffer, "Sharks VS Babies", 32, 32);
	alt_up_char_buffer_string(char_buffer, "Press 'A' to start", 30, 40);
	/*alt_up_char_buffer_string(char_buffer, "Load Game", 35, 38);
	alt_up_char_buffer_string(char_buffer, "Options", 36, 40);
	alt_up_char_buffer_string(char_buffer, "Help", 38, 42);*/

	while(data != 0x1c){ //wait for user to press start

		//Default Shark image
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 160, 80, 176, 84, 0x0099, 0);
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 160, 99, 176, 103, 0x0099, 0);
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 160, 84, 176, 99, 0xCEFD, 0);

		//Shark opens mouth
		for(j = 0; j < 500000; j++);
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 160, 84, 172, 100, 0xCEFD, 0);
		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 160, 90, 168, 96, 0x0099, 0);
		for(k = 0; k < 550000; k++);
		decode_scancode(ps2_kb, &decode_mode, &data, &ascii);

	}





	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
	alt_up_char_buffer_clear(char_buffer);
	//wave_scroll(pixel_buffer);




}
