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

#include <stdio.h>
#include "altera_up_ps2_keyboard.h"
#include "altera_up_avalon_ps2.h"
#include "altera_up_avalon_ps2_regs.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"

#include "title_screen.h"
#include "graphics.h"
#include "game_structs.h"


#define PS2_NAME "/dev/ps2"
#define PS2_TYPE "altera_up_avalon_ps2"
#define PS2_BASE 0x00004030
#define PS2_SPAN 8
#define PS2_IRQ 0
#define PS2_HDL_PARAMETERS ""
#define ALT_MODULE_CLASS_ps2 altera_up_avalon_ps2


void tower_selection(Tower*, alt_up_ps2_dev* , KB_CODE_TYPE , alt_u8 , char );


/*main gameplay cursor logic, with some title screen features .. will have to seperate*/
int main()
{
	KB_CODE_TYPE decode_mode;
	alt_u8 data;
	char ascii;
	char *p;
	int start = 0;
	int i;
	int num_babies = 0;


	//Tower* baby = (Tower*)malloc(16 * sizeof (Tower));
	Tower baby[16];
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

			if(data == 0x16 || data == 0x1E || data == 0x26){
			tower_selection(&baby[num_babies], ps2_kb, decode_mode, data, ascii);
			}

			if(data == 0x1c){ // user presses A
				initialize_baby(&baby[num_babies], baby[num_babies].health, baby[num_babies].bullet, baby[num_babies].fire_rate, grid_pos , baby[num_babies].colour);
				//draw_baby(baby[num_babies].body_pos, baby[num_babies].diaper_pos, baby[num_babies].colour, pixel_buffer);
				draw_baby(&baby[num_babies], pixel_buffer);

				num_babies++;
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


void tower_selection(Tower* baby, alt_up_ps2_dev *ps2_kb, KB_CODE_TYPE decode_mode, alt_u8 data, char ascii){

	//if (decode_scancode(ps2_kb, &decode_mode, &data, &ascii)==0)
	//{

		if(data == 0x16){  //if user presses 1 : Dairy Cow (Resource Generator)

			baby->colour = 0x0000;
			baby->health = 50;
			baby->fire_rate = 0;
			baby->bullet = 0;


		}

		else if(data == 0x1E){  //if user presses 2 : Infant-ry

			baby->colour = 0xFE99;
			baby->health = 100;
			baby->fire_rate = 25;
			baby->bullet = 0;


		}

		else if(data == 0x26){  //if user presses 3 : Rapid-fire Rugrat

			baby->colour = 0xFFE0;
			baby->health = 75;
			baby->fire_rate = 50;
			baby->bullet = 0;

		}







	//}



}





