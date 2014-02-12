/*
 * help_menu.c
 *
 *  Created on: Feb 9, 2014
 *      Author: Keval
 */

#include "help_menu.h"

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
	alt_up_char_buffer_string(char_buffer, "Resources can be acquired in two ways:", 3, 35);
	alt_up_char_buffer_string(char_buffer, "1) Resources will periodically fall from the sky. The player can attempt to", 3, 38);
	alt_up_char_buffer_string(char_buffer, "obtain these resources by navigating a boat at the top of the screen.", 3, 40);
	alt_up_char_buffer_string(char_buffer, "There are three types of resources, each yielding a different amount.", 3, 42);
	alt_up_char_buffer_string(char_buffer, "2) The player can place a resource generating tower that slowly generates", 3, 45);
	alt_up_char_buffer_string(char_buffer, "resources for the player. Note that these towers cannot attack the enemies", 3, 47);
	alt_up_char_buffer_string(char_buffer, "and have low HP.", 3, 49);

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
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 10, 82, 50, 132, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: XXX", 3, 22);
	alt_up_char_buffer_string(char_buffer, "COST: XXX", 3, 24);
	alt_up_char_buffer_string(char_buffer, "DMG: XXX", 3, 26);
	alt_up_char_buffer_string(char_buffer, "F.RATE: X", 3, 28);
	alt_up_char_buffer_string(char_buffer, "EFF: XXX", 3, 30);

	/* Tower Row 1 Col 2 */
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 62, 40, 102, 80, RED, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 62, 82, 102, 132, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: XXX", 16, 22);
	alt_up_char_buffer_string(char_buffer, "COST: XXX", 16, 24);
	alt_up_char_buffer_string(char_buffer, "DMG: XXX", 16, 26);
	alt_up_char_buffer_string(char_buffer, "F.RATE: X", 16, 28);
	alt_up_char_buffer_string(char_buffer, "EFF: XXX", 16, 30);

	/* Tower Row 1 Col 3 */
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 114, 40, 154, 80, RED, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 114, 82, 154, 132, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: XXX", 29, 22);
	alt_up_char_buffer_string(char_buffer, "COST: XXX", 29, 24);
	alt_up_char_buffer_string(char_buffer, "DMG: XXX", 29, 26);
	alt_up_char_buffer_string(char_buffer, "F.RATE: X", 29, 28);
	alt_up_char_buffer_string(char_buffer, "EFF: XXX", 29, 30);

	/* Tower Row 1 Col 4 */
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 166, 40, 204, 80, RED, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 166, 82, 204, 132, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: XXX", 42, 22);
	alt_up_char_buffer_string(char_buffer, "COST: XXX", 42, 24);
	alt_up_char_buffer_string(char_buffer, "DMG: XXX", 42, 26);
	alt_up_char_buffer_string(char_buffer, "F.RATE: X", 42, 28);
	alt_up_char_buffer_string(char_buffer, "EFF: XXX", 42, 30);

	/* Tower Row 1 Col 5 */
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 218, 40, 258, 80, RED, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 218, 82, 258, 132, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: XXX", 55, 22);
	alt_up_char_buffer_string(char_buffer, "COST: XXX", 55, 24);
	alt_up_char_buffer_string(char_buffer, "DMG: XXX", 55, 26);
	alt_up_char_buffer_string(char_buffer, "F.RATE: X", 55, 28);
	alt_up_char_buffer_string(char_buffer, "EFF: XXX", 55, 30);


	/* Tower Row 2 Col 1 */
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 10, 140, 50, 180, RED, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 10, 182, 50, 232, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: XXX", 3, 47);
	alt_up_char_buffer_string(char_buffer, "COST: XXX", 3, 49);
	alt_up_char_buffer_string(char_buffer, "DMG: XXX", 3, 51);
	alt_up_char_buffer_string(char_buffer, "F.RATE: X", 3, 53);
	alt_up_char_buffer_string(char_buffer, "EFF: XXX", 3, 55);

	/* Tower Row 2 Col 2 */
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 62, 140, 102, 180, RED, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 62, 182, 102, 232, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: XXX", 16, 47);
	alt_up_char_buffer_string(char_buffer, "COST: XXX", 16, 49);
	alt_up_char_buffer_string(char_buffer, "DMG: XXX", 16, 51);
	alt_up_char_buffer_string(char_buffer, "F.RATE: X", 16, 53);
	alt_up_char_buffer_string(char_buffer, "EFF: XXX", 16, 55);

	/* Tower Row 2 Col 3 */
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 114, 140, 154, 180, RED, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 114, 182, 154, 232, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: XXX", 29, 47);
	alt_up_char_buffer_string(char_buffer, "COST: XXX", 29, 49);
	alt_up_char_buffer_string(char_buffer, "DMG: XXX", 29, 51);
	alt_up_char_buffer_string(char_buffer, "F.RATE: X", 29, 53);
	alt_up_char_buffer_string(char_buffer, "EFF: XXX", 29, 55);

	/* Tower Row 2 Col 4 */
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 166, 140, 204, 180, RED, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 166, 182, 204, 232, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: XXX", 42, 47);
	alt_up_char_buffer_string(char_buffer, "COST: XXX", 42, 49);
	alt_up_char_buffer_string(char_buffer, "DMG: XXX", 42, 51);
	alt_up_char_buffer_string(char_buffer, "F.RATE: X", 42, 53);
	alt_up_char_buffer_string(char_buffer, "EFF: XXX", 42, 55);
}

void draw_sharks_guide(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev* char_buffer){
	alt_up_char_buffer_clear(char_buffer);
	draw_menu_text(char_buffer);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 31, 320, 240, BLACK, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 70, 10, 140, 30, BLUE, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 195, 10, 260, 30, BLUE, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 140, 10, 190, 30, YELLOW, 0);

	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 62, 40, 102, 80, RED, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 62, 82, 102, 132, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: XXX", 16, 22);
	alt_up_char_buffer_string(char_buffer, "DMG: XXX", 16, 24);
	alt_up_char_buffer_string(char_buffer, "A.RATE: X", 16, 26);
	alt_up_char_buffer_string(char_buffer, "SPEED: XX", 16, 28);
	alt_up_char_buffer_string(char_buffer, "EFF: XXX", 16, 30);

	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 114, 40, 154, 80, RED, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 114, 82, 154, 132, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: XXX", 29, 22);
	alt_up_char_buffer_string(char_buffer, "DMG: XXX", 29, 24);
	alt_up_char_buffer_string(char_buffer, "A.RATE: X", 29, 26);
	alt_up_char_buffer_string(char_buffer, "SPEED: XX", 29, 28);
	alt_up_char_buffer_string(char_buffer, "EFF: XXX", 29, 30);

	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 166, 40, 204, 80, RED, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 166, 82, 204, 132, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: XXX", 42, 22);
	alt_up_char_buffer_string(char_buffer, "DMG: XXX", 42, 24);
	alt_up_char_buffer_string(char_buffer, "A.RATE: X", 42, 26);
	alt_up_char_buffer_string(char_buffer, "SPEED: XX", 42, 28);
	alt_up_char_buffer_string(char_buffer, "EFF: XXX", 42, 30);

	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 218, 40, 258, 80, RED, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 218, 82, 258, 132, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: XXX", 55, 22);
	alt_up_char_buffer_string(char_buffer, "DMG: XXX", 55, 24);
	alt_up_char_buffer_string(char_buffer, "A.RATE: X", 55, 26);
	alt_up_char_buffer_string(char_buffer, "SPEED: XX", 55, 28);
	alt_up_char_buffer_string(char_buffer, "EFF: XXX", 55, 30);

	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 114, 140, 154, 180, RED, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 114, 182, 154, 232, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: XXX", 29, 47);
	alt_up_char_buffer_string(char_buffer, "DMG: XXX", 29, 49);
	alt_up_char_buffer_string(char_buffer, "A.RATE: X", 29, 51);
	alt_up_char_buffer_string(char_buffer, "SPEED: XX", 29, 53);
	alt_up_char_buffer_string(char_buffer, "EFF: XXX", 29, 55);

	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 166, 140, 204, 180, RED, 0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 166, 182, 204, 232, WHITE, 0);
	alt_up_char_buffer_string(char_buffer, "HP: XXX", 42, 47);
	alt_up_char_buffer_string(char_buffer, "DMG: XXX", 42, 49);
	alt_up_char_buffer_string(char_buffer, "A.RATE: X", 42, 51);
	alt_up_char_buffer_string(char_buffer, "SPEED: XX", 42, 53);
	alt_up_char_buffer_string(char_buffer, "EFF: XXX", 42, 55);

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
	alt_up_char_buffer_string(char_buffer, "A ------------ Move Resource Collecting Boat Left", 17, 31);
	alt_up_char_buffer_string(char_buffer, "D ------------ Move Resource Collecting Boat Right", 17, 34);
	alt_up_char_buffer_string(char_buffer, "(1 to 9) ----- Select Tower To Place", 17, 37);
	alt_up_char_buffer_string(char_buffer, "SPACEBAR ----- Place Tower On Current Grid ", 17, 40);
	alt_up_char_buffer_string(char_buffer, "ESC ---------- Pause Menu / Return To Previous Menu", 17, 43);
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
