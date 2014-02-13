/*
 * main_game.c
 *
 *  Created on: 2014-02-07
 *      Author: Cyril
 */
#include <stdio.h>
#include <stdlib.h>
#include "altera_up_ps2_keyboard.h"
#include "altera_up_avalon_ps2.h"
#include "altera_up_avalon_ps2_regs.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"
#include "level_one.h"
#include "keyboard_codes.h"
#include "game_structs.h"
#include "Colors.h"
#include "heads_up_display.h"
#include "background_graphics.h"
#include "cursor.h"
#include "graphics.h"
#include "interrupt_funcs.h"
#include "tower_select.h"
#include "game_over.h"

extern alt_up_pixel_buffer_dma_dev* pixel_buffer;
extern int gameOverFlag;
extern int victoryFlag;


//Level dependent values for use in interrupts
extern int maxEnemy;
extern int numEnemy;
extern int resources;



void mainGame_level2(alt_up_ps2_dev *ps2_kb, KB_CODE_TYPE decode_mode, alt_u8 data, char ascii){

	//set starting grid position to be grid 6, which is the top left-most grid
	int i;
	int grid_pos = 6;
	int temp_baby_attributes[10] = {0};
	int hasTowerBeenSelected = 0;   //flag that checks if user has selected a tower for placement
	int hasTowerBeenPlaced = 0;		// flag that checks when a tower has been placed
	int towerCanBePlaced = 0;		// flag that checks whether a tower can be placed	(
	int hasCursorMoved = 0;			//flag that checks if the cursor is being told to move (helps fix sensitivity)


	//Level dependent values for use in interrupts
	maxEnemy = 15;
	numEnemy = 0;
	resources = 40;



	dataPtr game_data = malloc(sizeof(gameData));
	for(i = 0; i < NUMROW; i++){
		game_data->eneHead[i] = NULL;
	}

	// set positions of baby towers
	set_baby_positions(game_data->towers);

	//clear pixel buffer memory
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
	//clear pixel buffer memory
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 1);
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
	{


		if (decode_scancode(ps2_kb, &decode_mode, &data, &ascii)==0)
		{


				//if user presses one of the number keys (1 -6 for level 2)
				if(data == ONE_KEY || data == TWO_KEY || data == THREE_KEY || data == FOUR_KEY || data == FIVE_KEY || data == SIX_KEY){
					//enter tower selection function, and raise hasTowerBeenSelected flag
					tower_selection(ps2_kb, decode_mode, data, ascii, temp_baby_attributes);

					hasTowerBeenSelected++;
				}

				// first check if a tower can be placed (i.e. a user has already selected a tower) and if there is
				// already an existing tower in that grid (in that case, don't place anything)
				// draw the baby on the current grid position, raise hasTowerBeenPlaced flag and reset
				// hasTowerBeenSelected + towerCanBePlaced flags, set tower isAlive status to 1
				else if(data == SPACEBAR && towerCanBePlaced == 1 && (game_data->towers[grid_pos]->isAlive == 0 && grid_pos!= 1 && grid_pos!= 3 && grid_pos!= 9 && grid_pos!= 11 && grid_pos!= 15 && grid_pos!= 17 && grid_pos!= 23 && grid_pos!= 25)&& temp_baby_attributes[0] <= resources){ // user presses SPACEBAR
					resources -= temp_baby_attributes[0];


					//TOREMOVE
					printf("resources after spend: %i", resources);

					set_baby_attributes(game_data->towers, grid_pos, temp_baby_attributes);

					draw_baby(game_data->towers[grid_pos], pixel_buffer, game_data->towers[grid_pos]->bulletType);
					game_data->towers[grid_pos]->isAlive = 1;

					hasTowerBeenPlaced++;
					hasTowerBeenSelected = 0;
					towerCanBePlaced = 0;

				}

		/*		else if(data == ESC) {
				//	switch_to_menu(pixel_buffer, char_buffer, ps2_kb, decode_mode);
				}*/

				//If player presses B while cursor highlights a tower, the tower is removed
				else if(data == B_KEY && (game_data->towers[grid_pos]->isAlive == 1)){

					remove_baby(game_data->towers[grid_pos], grid_pos, pixel_buffer);
				}

				//check if user has pressed any of the directional keys, update the cursor moved flag
				else if(data == UP || data == DOWN || data == LEFT || data == RIGHT){
					hasCursorMoved++;
				}

				else{



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

			//num_babies = (num_babies + 1)% 14;
			hasTowerBeenPlaced = 0;

		}

	}
	alt_irq_disable(TIMER_0_IRQ);
	freeEverything(game_data);
	free(game_data);

}
