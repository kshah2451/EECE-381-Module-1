/*
 * help_menu.c
 *
 *  Created on: Feb 9, 2014
 *      Author: Keval
 */

#include "help_menu.h"
#include "bitmaps.h"
#include "background_graphics.h"

void draw_help_babies(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev * char_buffer, int tower_type, int x_pos, int y_pos);

void draw_help_menu(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev* char_buffer, alt_up_ps2_dev *ps2_kb, KB_CODE_TYPE  decode_mode) {
	int count = 0;
	int exit_flag = 0;
	int current_menu = HOW_TO_PLAY_MENU;
	alt_u8 data;
	char ascii;
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 10, 319, 30, BLUE, 0);
	draw_menu_text(char_buffer);
	draw_how_to_play_guide(pixel_buffer, char_buffer);
	while(exit_flag == 0) {
		if (decode_scancode(ps2_kb, &decode_mode, &data, &ascii) == 0) {
			if(data == LEFT || data == RIGHT || data == ESC) count++;
			if(data == LEFT && count >= 2) {
				if(current_menu != HOW_TO_PLAY_MENU) current_menu--;
				draw_current_menu(pixel_buffer, char_buffer, current_menu);
				count = 0;
			}
			if(data == RIGHT && count >= 2) {
				if(current_menu != DEVS_MENU) current_menu++;
				draw_current_menu(pixel_buffer, char_buffer, current_menu);
				count = 0;
			}
			if(data == ESC && count >= 2) {
				exit_flag = 1;
			}
		}

	}
	alt_up_char_buffer_clear(char_buffer);
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
}

void draw_current_menu(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev* char_buffer, int current_menu){
	switch(current_menu) {
	case HOW_TO_PLAY_MENU:
		draw_how_to_play_guide(pixel_buffer, char_buffer);
		break;
	case TOWERS_MENU:
		draw_towers_guide(pixel_buffer, char_buffer);
		break;
	case SHARKS_MENU:
		draw_sharks_guide(pixel_buffer, char_buffer);
		break;
	case CONTROLS_MENU:
		draw_controls_guide(pixel_buffer, char_buffer);
		break;
	case DEVS_MENU:
		draw_developers_guide(pixel_buffer, char_buffer);
		break;
	}
}


void draw_menu_text(alt_up_char_buffer_dev* char_buffer) {
	alt_up_char_buffer_string(char_buffer, "HOW TO PLAY", 3, 5);
	alt_up_char_buffer_string(char_buffer, "TOWERS", 23, 5);
	alt_up_char_buffer_string(char_buffer, "SHARKS", 38, 5);
	alt_up_char_buffer_string(char_buffer, "CONTROLS", 53, 5);
	alt_up_char_buffer_string(char_buffer, "DEVS", 70, 5);
}

void clear_menu_text(alt_up_char_buffer_dev* char_buffer) {
	alt_up_char_buffer_string(char_buffer, "           ", 3, 5);
	alt_up_char_buffer_string(char_buffer, "      ", 23, 5);
	alt_up_char_buffer_string(char_buffer, "      ", 38, 5);
	alt_up_char_buffer_string(char_buffer, "        ", 53, 5);
	alt_up_char_buffer_string(char_buffer, "    ", 70, 5);
}

void draw_how_to_play_guide(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev* char_buffer) {
	alt_up_char_buffer_clear(char_buffer);
	draw_menu_text(char_buffer);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 31, 320, 240, BLACK, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 70, 10, 140, 30, BLUE, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 0, 10, 70, 30, YELLOW, 0);
	alt_up_char_buffer_string(char_buffer, "O B J E C T I V E", 3, 12);
	alt_up_char_buffer_string(char_buffer, "_________________", 3, 13);
	alt_up_char_buffer_string(char_buffer, "In SHARKS VS. BABIES, players play as babies, trying to protect their", 3, 15);
	alt_up_char_buffer_string(char_buffer, "base against the enemy sharks. The player can purchase towers using the", 3, 17);
	alt_up_char_buffer_string(char_buffer, "resources currently avalable to them and place them on a grid in order to", 3, 19);
	alt_up_char_buffer_string(char_buffer, "fight the enemy sharks. Each tower is unique and has different attributes.", 3, 21);
	alt_up_char_buffer_string(char_buffer, "However, be wary that each type of shark has different attributes and some", 3, 23);
	alt_up_char_buffer_string(char_buffer, "towers may be more or less effective against the different types of sharks.", 3, 25);
	alt_up_char_buffer_string(char_buffer, "The objective of the game is to prevent the sharks from reaching the dock.", 3, 27);
	alt_up_char_buffer_string(char_buffer, "A C Q U I R I N G  R E S O U R C E S", 3, 32);
	alt_up_char_buffer_string(char_buffer, "____________________________________", 3, 33);
	alt_up_char_buffer_string(char_buffer, "Resources can be acquired through the following:", 3, 35);

	alt_up_char_buffer_string(char_buffer, "* The player can place a resource generating tower that slowly generates", 3, 38);
	alt_up_char_buffer_string(char_buffer, "resources for the player. Note that these towers cannot attack the enemies", 3, 40);
	alt_up_char_buffer_string(char_buffer, "and have low HP.", 3, 42);

}

void draw_towers_guide(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev* char_buffer){
	alt_up_char_buffer_clear(char_buffer);
	draw_menu_text(char_buffer);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 31, 320, 240, BLACK, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 0, 10, 70, 30, BLUE, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 140, 10, 190, 30, BLUE, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 70, 10, 140, 30, YELLOW, 0);

	/* Tower Row 1 Col 1 */
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 10, 40, 50, 80, RED, 0);

	draw_help_babies(pixel_buffer, char_buffer, 1, 15, 45);

	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 10, 82, 50, 132, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: LOW", 3, 22);
	alt_up_char_buffer_string(char_buffer, "COST: 5", 3, 24);
	alt_up_char_buffer_string(char_buffer, "DMG: -", 3, 26);
	alt_up_char_buffer_string(char_buffer, "F.RATE: -", 3, 28);
	alt_up_char_buffer_string(char_buffer, "EFF: Milk", 3, 30);

	/* Tower Row 1 Col 2 */
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 62, 40, 102, 80, RED, 0);

	draw_help_babies(pixel_buffer, char_buffer, 2, 67, 45);

	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 62, 82, 102, 132, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: MED", 16, 22);
	alt_up_char_buffer_string(char_buffer, "COST: 7", 16, 24);
	alt_up_char_buffer_string(char_buffer, "DMG: MED", 16, 26);
	alt_up_char_buffer_string(char_buffer, "F.RATE: M", 16, 28);
	alt_up_char_buffer_string(char_buffer, "EFF: n/a", 16, 30);

	/* Tower Row 1 Col 3 */
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 114, 40, 154, 80, RED, 0);
	draw_help_babies(pixel_buffer, char_buffer, 3, 119, 45);

	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 114, 82, 154, 132, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: MED", 29, 22);
	alt_up_char_buffer_string(char_buffer, "COST:10", 29, 24);
	alt_up_char_buffer_string(char_buffer, "DMG: LOW", 29, 26);
	alt_up_char_buffer_string(char_buffer, "F.RATE: H", 29, 28);
	alt_up_char_buffer_string(char_buffer, "EFF:", 29, 30);
	alt_up_char_buffer_string(char_buffer, "Rapid-Fire", 29, 32);


	/* Tower Row 1 Col 4 */
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 166, 40, 204, 80, RED, 0);
	draw_help_babies(pixel_buffer, char_buffer, 4, 171, 45);

	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 166, 82, 204, 132, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: HI", 42, 22);
	alt_up_char_buffer_string(char_buffer, "COST:10", 42, 24);
	alt_up_char_buffer_string(char_buffer, "DMG: -", 42, 26);
	alt_up_char_buffer_string(char_buffer, "F.RATE:-", 42, 28);
	alt_up_char_buffer_string(char_buffer, "EFF: Wall", 42, 30);

	/* Tower Row 1 Col 5 */
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 218, 40, 258, 80, RED, 0);
	draw_help_babies(pixel_buffer, char_buffer, 5, 223, 45);

	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 218, 82, 258, 132, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: LOW", 55, 22);
	alt_up_char_buffer_string(char_buffer, "COST: 7", 55, 24);
	alt_up_char_buffer_string(char_buffer, "DMG: HI", 55, 26);
	alt_up_char_buffer_string(char_buffer, "F.RATE: L", 55, 28);
	alt_up_char_buffer_string(char_buffer, "EFF: Mine", 55, 30);


	/* Tower Row 2 Col 1 */
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 10, 140, 50, 180, RED, 0);

	draw_help_babies(pixel_buffer, char_buffer, 6, 15, 145);

	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 10, 182, 50, 232, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: MED", 3, 47);
	alt_up_char_buffer_string(char_buffer, "COST: 13", 3, 49);
	alt_up_char_buffer_string(char_buffer, "DMG: MED", 3, 51);
	alt_up_char_buffer_string(char_buffer, "F.RATE: M", 3, 53);
	alt_up_char_buffer_string(char_buffer, "EFF:", 3, 55);
	alt_up_char_buffer_string(char_buffer, "Freeze", 3, 57);
	/* Tower Row 2 Col 2 */
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 62, 140, 102, 180, RED, 0);
	draw_help_babies(pixel_buffer, char_buffer, 7, 67, 145);

	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 62, 182, 102, 232, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: LOW", 16, 47);
	alt_up_char_buffer_string(char_buffer, "COST: 13", 16, 49);
	alt_up_char_buffer_string(char_buffer, "DMG: LOW", 16, 51);
	alt_up_char_buffer_string(char_buffer, "F.RATE: M", 16, 53);
	alt_up_char_buffer_string(char_buffer, "EFF:", 16, 55);
	alt_up_char_buffer_string(char_buffer, "Poison", 16, 57);

	/* Tower Row 2 Col 3 */
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 114, 140, 154, 180, RED, 0);
	draw_help_babies(pixel_buffer, char_buffer, 8, 119, 145);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 114, 182, 154, 232, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: LOW", 29, 47);
	alt_up_char_buffer_string(char_buffer, "COST:15", 29, 49);
	alt_up_char_buffer_string(char_buffer, "DMG: HI", 29, 51);
	alt_up_char_buffer_string(char_buffer, "F.RATE: L", 29, 53);
	alt_up_char_buffer_string(char_buffer, "EFF:", 29, 55);
	alt_up_char_buffer_string(char_buffer, "Rocket", 29, 57);


}

void draw_sharks_guide(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev* char_buffer){
	alt_up_char_buffer_clear(char_buffer);
	draw_menu_text(char_buffer);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 31, 320, 240, BLACK, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 70, 10, 140, 30, BLUE, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 195, 10, 260, 30, BLUE, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 140, 10, 190, 30, YELLOW, 0);

	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 62, 40, 102, 80, RED, 0);
	draw_sharkfin(pixel_buffer, 67, 45, 0x7bef);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 62, 82, 102, 132, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: MED", 16, 22);
	alt_up_char_buffer_string(char_buffer, "DMG: MED", 16, 24);
	alt_up_char_buffer_string(char_buffer, "A.RATE: M", 16, 26);
	alt_up_char_buffer_string(char_buffer, "SPEED: M", 16, 28);
	alt_up_char_buffer_string(char_buffer, "EFF: n/a", 16, 30);

	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 114, 40, 154, 80, RED, 0);
	draw_sharkfin(pixel_buffer, 119, 45, 0xffff);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 114, 82, 154, 132, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: LOW", 29, 22);
	alt_up_char_buffer_string(char_buffer, "DMG: MED", 29, 24);
	alt_up_char_buffer_string(char_buffer, "A.RATE: M", 29, 26);
	alt_up_char_buffer_string(char_buffer, "SPEED: H", 29, 28);
	alt_up_char_buffer_string(char_buffer, "EFF: Fast", 29, 30);

	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 166, 40, 204, 80, RED, 0);
	draw_sharkfin(pixel_buffer, 171, 45, 0x0000);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 166, 82, 204, 132, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: HIGH", 42, 22);
	alt_up_char_buffer_string(char_buffer, "DMG: LOW", 42, 24);
	alt_up_char_buffer_string(char_buffer, "A.RATE: M", 42, 26);
	alt_up_char_buffer_string(char_buffer, "SPEED: L", 42, 28);
	alt_up_char_buffer_string(char_buffer, "EFF:", 42, 30);
	alt_up_char_buffer_string(char_buffer, "Armour", 42, 32);

	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 218, 40, 258, 80, RED, 0);
	draw_sharkfin(pixel_buffer, 223, 45, 0x00ff);

	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 218, 82, 258, 132, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: MED", 55, 22);
	alt_up_char_buffer_string(char_buffer, "DMG:HIGH", 55, 24);
	alt_up_char_buffer_string(char_buffer, "A.RATE: -", 55, 26);
	alt_up_char_buffer_string(char_buffer, "SPEED:M", 55, 28);
	alt_up_char_buffer_string(char_buffer, "EFF:", 55, 30);
	alt_up_char_buffer_string(char_buffer, "Kamikaze", 55, 32);

	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 114, 140, 154, 180, RED, 0);
	draw_sharkfin(pixel_buffer, 119, 145, 0x0ff0);

	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 114, 182, 154, 232, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: HIGH", 29, 47);
	alt_up_char_buffer_string(char_buffer, "DMG: HIGH", 29, 49);
	alt_up_char_buffer_string(char_buffer, "A.RATE: M", 29, 51);
	alt_up_char_buffer_string(char_buffer, "SPEED: L", 29, 53);
	alt_up_char_buffer_string(char_buffer, "EFF:", 29, 55);
	alt_up_char_buffer_string(char_buffer, "MiniBoss", 29, 57);


	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 166, 140, 204, 180, RED, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 166, 140, 204, 180, RED, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 166, 182, 204, 232, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "BEWARE", 43, 47);
	alt_up_char_buffer_string(char_buffer, "THE", 44, 51);
	alt_up_char_buffer_string(char_buffer, "SHARKS", 43, 55);

}

void draw_controls_guide(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev* char_buffer){
	alt_up_char_buffer_clear(char_buffer);
	draw_menu_text(char_buffer);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 31, 320, 240, BLACK, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 140, 10, 190, 30, BLUE, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 260, 10, 319, 30, BLUE, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 195, 10, 260, 30, YELLOW, 0);
	alt_up_char_buffer_string(char_buffer, "C O N T R O L S", 33, 12);
	alt_up_char_buffer_string(char_buffer, "_______________", 33, 13);
	alt_up_char_buffer_string(char_buffer, "UP ARROW ----- Move Cursor Up / Navigate Menus", 17, 19);
	alt_up_char_buffer_string(char_buffer, "DOWN ARROW --- Move Cursor Down / Navigate Menus", 17, 22);
	alt_up_char_buffer_string(char_buffer, "RIGHT ARROW -- Move Cursor Right / Navigate Menus", 17, 25);
	alt_up_char_buffer_string(char_buffer, "LEFT ARROW --- Move Cursor Left / Navigate Menus", 17, 28);

	alt_up_char_buffer_string(char_buffer, "(1 to 8) ----- Select Tower To Place", 17, 31);
	alt_up_char_buffer_string(char_buffer, "SPACEBAR ----- Place Tower On Current Grid ", 17, 34);
	alt_up_char_buffer_string(char_buffer, "ESC ---------- Return To Previous Menu", 17, 37);
}

void draw_developers_guide(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev* char_buffer){
	alt_up_char_buffer_clear(char_buffer);
	draw_menu_text(char_buffer);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 31, 320, 240, BLACK, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 195, 10, 260, 30, BLUE, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 260, 10, 319, 30, YELLOW, 0);
	alt_up_char_buffer_string(char_buffer, "D E V E L O P E R S", 31, 12);
	alt_up_char_buffer_string(char_buffer, "___________________", 31, 13);
	alt_up_char_buffer_string(char_buffer, "CYRIL CANONIZADO", 33, 19);
	alt_up_char_buffer_string(char_buffer, "DAVID LU", 37, 23);
	alt_up_char_buffer_string(char_buffer, "KEVAL SHAH", 36, 27);
	alt_up_char_buffer_string(char_buffer, "BRYCE TOWNS", 36, 31);
}




void draw_help_babies(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev * char_buffer, int tower_type, int x_pos, int y_pos){

	int i,j,k;
	int col_swap1 = 0;
	int col_swap2 = 0;
	int pixel_el = 0;


	unsigned short int image_to_draw[750];

	//Check which .bmp image to draw. Depends on what the tower on this grid's type is
	switch (tower_type){
	case 1:						//Cow

		// go through the bmp array, and draw image pixel by pixel, skipping transparent pixels.
		for(i = 0; i < 30; i++)
		{
			for(j = 0; j < 25; j++){

				if(cow_bmp[pixel_el]!= BLACK){
					alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_pos+j, y_pos+i,x_pos+j, y_pos+i, cow_bmp[pixel_el], 0);

				}
				pixel_el++;
			}


		}




		break;
	case 2:						// Normal

		for(i = 0; i < 30; i++)
		{
			for(j = 0; j < 25; j++){

				if(baby_bmp[pixel_el]!= BLACK){
					alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_pos+j, y_pos+i,x_pos+j, y_pos+i, baby_bmp[pixel_el], 0);

				}
				pixel_el++;
			}


		}



		break;
	case 3:						//Rapid Fire


		col_swap1 = 0xFFE0;
		col_swap2 = 0xFFD0;


		for(i = 0; i < 30; i++)
		{
			for(j = 0; j < 25; j++){

				if(baby_bmp[pixel_el]!= BLACK){

						if(baby_bmp[pixel_el] == 0x738E){

							alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_pos+j, y_pos+i,x_pos+j, y_pos+i, col_swap1, 0);
						}
						else if(baby_bmp[pixel_el] == 0xD2CB){
							alt_up_pixel_buffer_dma_draw_box(pixel_buffer,x_pos+j, y_pos+i,x_pos+j, y_pos+i, col_swap2, 0);

						}
						else {
							alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_pos+j, y_pos+i,x_pos+j, y_pos+i, baby_bmp[pixel_el], 0);
						}
				}
				pixel_el++;
			}

		}





		break;

	case 4:						//Diaper Wall
		for(i = 0; i < 30; i++)
		{
			for(j = 0; j < 25; j++){

				if(diaper_bmp[pixel_el]!= BLACK){
					alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_pos+j, y_pos+i,x_pos+j, y_pos+i, diaper_bmp[pixel_el], 0);

				}
				pixel_el++;
			}


		}
		break;

	case 5:						//Mine tower

		for(i = 0; i < 30; i++)
				{
					for(j = 0; j < 25; j++){

						if(mine_bmp[pixel_el]!= BLACK){
							alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_pos+j, y_pos+i,x_pos+j, y_pos+i, mine_bmp[pixel_el], 0);

						}
						pixel_el++;
					}


				}



				break;

	case 6:						//Ice

		col_swap1 = 0x2FF;
		col_swap2 = 0x0E;


		for(i = 0; i < 30; i++)
		{
			for(j = 0; j < 25; j++){

				if(baby_bmp[pixel_el]!= BLACK){

						if(baby_bmp[pixel_el] == 0x738E){

							alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_pos+j, y_pos+i,x_pos+j, y_pos+i, col_swap1, 0);
						}
						else if(baby_bmp[pixel_el] == 0xD2CB){
							alt_up_pixel_buffer_dma_draw_box(pixel_buffer,x_pos+j, y_pos+i,x_pos+j, y_pos+i, col_swap2, 0);

						}
						else {
							alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_pos+j, y_pos+i,x_pos+j, y_pos+i, baby_bmp[pixel_el], 0);
						}
				}
				pixel_el++;
			}

		}



		break;

	case 7:

		col_swap1 = 0xF00F;
		col_swap2 = 0xF00A;



		for(i = 0; i < 30; i++)
		{
			for(j = 0; j < 25; j++){

				if(baby_bmp[pixel_el]!= BLACK){

						if(baby_bmp[pixel_el] == 0x738E){

							alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_pos+j, y_pos+i,x_pos+j, y_pos+i, col_swap1, 0);
						}
						else if(baby_bmp[pixel_el] == 0xD2CB){
							alt_up_pixel_buffer_dma_draw_box(pixel_buffer,x_pos+j, y_pos+i,x_pos+j, y_pos+i, col_swap2, 0);

						}
						else {
							alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_pos+j, y_pos+i,x_pos+j, y_pos+i, baby_bmp[pixel_el], 0);
						}
				}
				pixel_el++;
			}

		}



		break;

	case 8:
		col_swap1= 0x0005;
		col_swap2 =0xBDF7;





		for(i = 0; i < 30; i++)
		{
			for(j = 0; j < 25; j++){

				if(baby_bmp[pixel_el]!= BLACK){

						if(baby_bmp[pixel_el] == 0x738E){

							alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_pos+j, y_pos+i,x_pos+j, y_pos+i, col_swap1, 0);
						}
						else if(baby_bmp[pixel_el] == 0xD2CB){
							alt_up_pixel_buffer_dma_draw_box(pixel_buffer,x_pos+j, y_pos+i,x_pos+j, y_pos+i, col_swap2, 0);

						}
						else {
							alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_pos+j, y_pos+i,x_pos+j, y_pos+i, baby_bmp[pixel_el], 0);
						}
				}
				pixel_el++;
			}

		}




		break;

	}




}




