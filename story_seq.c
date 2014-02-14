/*
 * story_screen.c
 *
 *  Created on: 2014-02-04
 *      Author: Cyril
 */
#include "story_seq.h"
#include "audio.h"

unsigned int *audio_buffer_first;
unsigned int *audio_buffer_second;
unsigned int *audio_buffer_third;

void pre_level_story_1(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev * char_buffer, alt_up_ps2_dev * ps2_kb, KB_CODE_TYPE decode_mode,alt_u8 data, char ascii){

	int spacebar_detected = 0;
	char text[500];
	alt_up_char_buffer_clear(char_buffer);

	while(spacebar_detected < 2){
		// display graphic
		alt_up_char_buffer_string(char_buffer, "Due to the recent events documented in films such as \"Sharknado\" and", 2, 20);
		alt_up_char_buffer_string(char_buffer, "\"Sharktopus\" the UN assembled an international team of scientists to ", 2, 23);
		alt_up_char_buffer_string(char_buffer, "help defend mankind against the vicious onslaught of sharks. An estimate", 2, 26);
		alt_up_char_buffer_string(char_buffer, "was made of 20 years until the next shark attack.", 2, 29);
		alt_up_char_buffer_string(char_buffer, "Proposed method of defense:  genetically engineered super-soldiers.", 2, 32);
		alt_up_char_buffer_string(char_buffer, "Press SPACEBAR to continue", 40, 50);
		if(decode_scancode(ps2_kb, &decode_mode, &data, &ascii)== 0){
			if(data == SPACEBAR){
				spacebar_detected++;
			}
		}
	}
	spacebar_detected = 0;
	alt_up_char_buffer_clear(char_buffer);

	while(spacebar_detected < 2){
			// display graphic
		alt_up_char_buffer_string(char_buffer, "However, as the team of scientists was composed of international members,", 2, 20);
		alt_up_char_buffer_string(char_buffer, "was composed of international members, an error was made in the estimation", 2, 23);
		alt_up_char_buffer_string(char_buffer, "due to a failure to convert imperial to metric. The next shark attack was", 2, 26);
		alt_up_char_buffer_string(char_buffer, "going to occur in 20 months, not 20 years! Today the sharks begin their", 2, 29);
		alt_up_char_buffer_string(char_buffer, "invasion. Having no other method of defense, humanity must send out its", 2, 32);
		alt_up_char_buffer_string(char_buffer, "not-fully-developed super soldiers, right now. Godspeed. ", 2, 35);
		alt_up_char_buffer_string(char_buffer, "Press SPACEBAR to continue", 40, 50);
		if(decode_scancode(ps2_kb, &decode_mode, &data, &ascii)== 0){
			if(data == SPACEBAR){
					spacebar_detected++;
				}
			}
		}


	alt_up_char_buffer_string(char_buffer, "Loading....                      ", 40, 50);
	//LOAD HERE
	//audio_buffer_first = load_audio(1);
	alt_up_char_buffer_clear(char_buffer);
	tracker_l=22;
	tracker_r=22;
}


void pre_level_story_2(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev * char_buffer, alt_up_ps2_dev * ps2_kb, KB_CODE_TYPE decode_mode,alt_u8 data, char ascii){

	int spacebar_detected = 0;
	char text[500];
	alt_up_char_buffer_clear(char_buffer);

	while(spacebar_detected < 2){
		// display graphic
		alt_up_char_buffer_string(char_buffer, "Having been surprised by the super soldiers during the first wave of", 2, 20);
		alt_up_char_buffer_string(char_buffer, "invasion, the sharks turned to strategy rather than brute force.", 2, 23);
		alt_up_char_buffer_string(char_buffer, "Forming an alliance with the jellyfish, they schemed to stop the", 2, 26);
		alt_up_char_buffer_string(char_buffer, "soldiers from taking advantageous positions. To combat the new threat,", 2, 29);
		alt_up_char_buffer_string(char_buffer, "humanity has employed the use of mines, shark-slowing ice guns,", 2, 32);
		alt_up_char_buffer_string(char_buffer, "poison guns, and rocket launchers. These guns should help give humanity", 2, 35);
		alt_up_char_buffer_string(char_buffer, "the winning edge. One last push and its all over!", 2, 38);
		alt_up_char_buffer_string(char_buffer, "Press SPACEBAR to continue", 40, 50);

		if(decode_scancode(ps2_kb, &decode_mode, &data, &ascii)== 0){
			if(data == SPACEBAR){
				spacebar_detected++;
			}
		}
	}

	alt_up_char_buffer_string(char_buffer, "Loading Level 2....                      ", 40, 50);
	//LOAD HERE
	//audio_buffer_second = load_audio(2);
	alt_up_char_buffer_clear(char_buffer);
	tracker_l=22;
	tracker_r=22;
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

	alt_up_char_buffer_string(char_buffer, "Loading Final Level....                      ", 40, 50);
	//LOAD HERE
	//audio_buffer_third = load_audio(3);
	tracker_l=22;
	tracker_r=22;

}

