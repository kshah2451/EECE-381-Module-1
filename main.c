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
#include <stdlib.h>
#include "altera_up_ps2_keyboard.h"
#include "altera_up_avalon_ps2.h"
#include "altera_up_avalon_ps2_regs.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"

#include "title_screen.h"
#include "graphics.h"
#include "game_structs.h"
#include "interrupt_funcs.h"
#include "background_graphics.h"
#include "tower_select.h"
#include "cursor.h"
#include "system.h"
#include "heads_up_display.h"
#include "keyboard_codes.h"
//#include "bitmaps.h"
#include "game_over.h"


//GLOBAL VARIABLES
alt_up_pixel_buffer_dma_dev* pixel_buffer;
int gameOverFlag = 0;
int victoryFlag = 0;




/*main gameplay cursor logic, with some title screen features .. will have to seperate*/
int main()
{
	KB_CODE_TYPE decode_mode;
	alt_u8 data;
	char ascii;
	char *p;
	int temp_baby_attributes[10] = {0};
	int start = 0;		//i dont think im actually using this... will have to check
	int num_babies = 0; //i dont think im actually using this... will have to check
	int i;
	dataPtr game_data = (dataPtr)malloc(sizeof(gameData));
	for(i = 0; i < NUMROW; i++){
		game_data->eneHead[i] = NULL;
	}

	//set starting grid position to be grid 6, which is the top left-most grid
	int grid_pos = 6;
	int hasTowerBeenSelected = 0;   //flag that checks if user has selected a tower for placement
	int hasTowerBeenPlaced = 0;		// flag that checks when a tower has been placed
	int towerCanBePlaced = 0;		// flag that checks whether a tower can be placed	(
	int hasCursorMoved = 0;			//flag that checks if the cursor is being told to move (helps fix sensitivity)


				/* HAL INITIALIZATIONS*/



	// set positions of baby towers
	set_baby_positions(game_data->towers);

	//bunch of keyboard initializations
	alt_up_ps2_dev *ps2_kb;
	ps2_kb=alt_up_ps2_open_dev("/dev/ps2");
	alt_up_ps2_init(ps2_kb);
	alt_up_ps2_clear_fifo(ps2_kb);

	//pixel buffer initializations

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







					/* TITLE SCREEN*/
				// display the title screen
	title_screen(pixel_buffer, char_buffer, start, ps2_kb, decode_mode, data, ascii); //wait here until "ENTER"

	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);


	//set background image
	draw_sky(pixel_buffer);

	draw_ocean(pixel_buffer);

	draw_grids(pixel_buffer);
	heads_up_display_static();




	//set default cursor position to be grid 6
	set_cursor(grid_pos, CURSOR_COLOUR);
	draw_cursor(cur.pos,cur.colour, pixel_buffer);
	alt_irq_register(TIMER_0_IRQ, game_data, &timerroutine);
	while(gameOverFlag == 0 && victoryFlag < 10)
//	while(1)
	{

		if (decode_scancode(ps2_kb, &decode_mode, &data, &ascii)==0)
		{

				printf("What was pressed: %x \n", data);
				//if user presses one of the number keys (1 and 2 and 3 for now)
				if(data == ONE_KEY || data == TWO_KEY || data == THREE_KEY){
					//enter tower selection function, and raise hasTowerBeenSelected flag
					tower_selection(ps2_kb, decode_mode, data, ascii, temp_baby_attributes);

					hasTowerBeenSelected++;
				}

				// first check if a tower can be placed (i.e. a user has already selected a tower) and if there is
				// already an existing tower in that grid (in that case, don't place anything)
				// draw the baby on the current grid position, raise hasTowerBeenPlaced flag and reset
				// hasTowerBeenSelected + towerCanBePlaced flags, set tower isAlive status to 1
				else if(data == SPACEBAR && towerCanBePlaced == 1 && (game_data->towers[grid_pos]->isAlive == 0)){ // user presses A
					set_baby_attributes(game_data->towers, grid_pos, temp_baby_attributes);
					printf("data = %x when it goes in else if \n", data);
					draw_baby(game_data->towers[grid_pos], pixel_buffer, game_data->towers[grid_pos]->bulletType);
					game_data->towers[grid_pos]->isAlive = 1;

					hasTowerBeenPlaced++;
					hasTowerBeenSelected = 0;
					towerCanBePlaced = 0;

				}

				//If player presses B while cursor highlights a tower, the tower is removed
				else if(data == B_KEY && (game_data->towers[grid_pos]->isAlive == 1)){

					remove_baby(game_data->towers[grid_pos], grid_pos, pixel_buffer);
				}

				//check if user has pressed any of the directional keys, update the cursor moved flag
				else if(data == UP || data == DOWN || data == LEFT || data == RIGHT){
					hasCursorMoved++;
				}

				else{

					printf("data = %x when incorrect key pressed \n", data);

				}

					//only when cursor moved >= 2 (because of keyboard sensitivity, move the cursor
					if(hasCursorMoved >= 2){
						//move the cursor and update the grid position
						grid_pos = move_cursor(grid_pos, ps2_kb, decode_mode, data, ascii, pixel_buffer);
						//reset hasCursorMoved flag
						hasCursorMoved = 0;

						}




			}

		// Check if player has chosen a tower to spawn
		if(hasTowerBeenSelected >= 2){
			towerCanBePlaced = 1;
		}

		// Check if player has just placed a new tower
		if(hasTowerBeenPlaced >= 2){

			num_babies = (num_babies + 1)% 14;
			hasTowerBeenPlaced = 0;

		}

	}
	alt_irq_disable(TIMER_0_IRQ);


	if(gameOverFlag == 1){
	gameover(pixel_buffer,char_buffer);
	}
	else if(victoryFlag >= 10){
		victory(pixel_buffer, char_buffer);
	}


  return 0;
}




