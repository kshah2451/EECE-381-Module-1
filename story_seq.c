/*
 * story_screen.c
 *
 *  Created on: 2014-02-04
 *      Author: Cyril
 */
#include "story_seq.h"

void pre_level_story_1(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev * char_buffer, alt_up_ps2_dev * ps2_kb, KB_CODE_TYPE decode_mode,alt_u8 data, char ascii){

	int spacebar_detected = 0;
	char text[500];
	alt_up_char_buffer_clear(char_buffer);

	while(spacebar_detected < 2){
		// display graphic
		alt_up_char_buffer_string(char_buffer, "Et Tu, Brute?", 32, 32);
		alt_up_char_buffer_string(char_buffer, "Press SPACEBAR to continue", 40, 50);
		if(decode_scancode(ps2_kb, &decode_mode, &data, &ascii)== 0){
			if(data == SPACEBAR){
				spacebar_detected++;
			}
		}
	}

}


void pre_level_story_2(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev * char_buffer, alt_up_ps2_dev * ps2_kb, KB_CODE_TYPE decode_mode,alt_u8 data, char ascii){

	int spacebar_detected = 0;
	char text[500];
	alt_up_char_buffer_clear(char_buffer);

	while(spacebar_detected < 2){
		// display graphic
		alt_up_char_buffer_string(char_buffer, "Long ago in a distant land, I, Aku, the shape-shifting Master of Darkness, unleashed an unspeakable evil!", 8, 32);
		alt_up_char_buffer_string(char_buffer, "But a foolish Samurai warrior wielding a magic sword stepped forth to oppose me.", 8, 34);
		alt_up_char_buffer_string(char_buffer,"Before the final blow was struck, I tore open a portal in time and flung him into the future, where my evil is law!", 8, 36);
		alt_up_char_buffer_string(char_buffer,"Now the fool seeks to return to the past, and undo the future that is Aku!", 8, 38);
		alt_up_char_buffer_string(char_buffer, "Press SPACEBAR to continue", 40, 50);
		if(decode_scancode(ps2_kb, &decode_mode, &data, &ascii)== 0){
			if(data == SPACEBAR){
				spacebar_detected++;
			}
		}
	}

}

void pre_level_story_3(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev * char_buffer, alt_up_ps2_dev * ps2_kb, KB_CODE_TYPE decode_mode,alt_u8 data, char ascii){

	int spacebar_detected = 0;
	char text[500];
	alt_up_char_buffer_clear(char_buffer);

	while(spacebar_detected < 2){
		// display graphic
		alt_up_char_buffer_string(char_buffer, "8==========D", 15, 32);

		alt_up_char_buffer_string(char_buffer, "Press SPACEBAR to continue", 40, 50);
		if(decode_scancode(ps2_kb, &decode_mode, &data, &ascii)== 0){
			if(data == SPACEBAR){
				spacebar_detected++;
			}
		}
	}

}

