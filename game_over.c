#include "game_over.h"
#include "interrupt_funcs.h"
#include "audio.h"

void display_score(int score){


}


void victory(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev * char_buffer, alt_up_ps2_dev *ps2_kb, KB_CODE_TYPE decode_mode, alt_u8 data, char ascii){
	int color_inc = 0x0100;
	int x0_pos = 0;
	int x1_pos = 320;
	int change = 4;
	int y_pos;

	alt_up_audio_dev *audio;
	audio = alt_up_audio_open_dev("/dev/audio_0");
	unsigned int* audio_buffer_victory;


	draw_sky(pixel_buffer);
	draw_ocean(pixel_buffer);
	draw_boardwalk(pixel_buffer);

	draw_tower(pixel_buffer, 40, 120, 1);
	draw_tower(pixel_buffer, 70, 120, 2);
	draw_tower(pixel_buffer, 100, 120, 3);
	draw_tower(pixel_buffer, 130, 120, 4);
	draw_tower(pixel_buffer, 160, 120, 5);
	draw_tower(pixel_buffer, 190, 120, 6);
	draw_tower(pixel_buffer, 220, 120, 7);
	draw_tower(pixel_buffer, 250, 120, 8);






	alt_up_char_buffer_clear(char_buffer);
	audio_buffer_victory = load_audio(99);

	tracker_l=22;
	tracker_r=22;
	play_once(audio_buffer_victory,audio,99);
	alt_up_char_buffer_string(char_buffer, "YOU WIN!", 36, 15);
	alt_up_char_buffer_string(char_buffer, "PRESS A TO CONTINUE", 32, 42);

	free(audio_buffer_victory);
	while(data != A_KEY){

		decode_scancode(ps2_kb, &decode_mode, &data, &ascii);
	}

	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);

}



void gameover(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev * char_buffer, alt_up_ps2_dev *ps2_kb, KB_CODE_TYPE decode_mode, alt_u8 data, char ascii){
	int color_inc = 0x0100;
	int x0_pos = 0;
	int x1_pos = 320;
	int change = 4;
	int y_pos;
	int enter_check = 0;

	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);

	alt_up_audio_dev *audio;
	audio = alt_up_audio_open_dev("/dev/audio_0");
	unsigned int* audio_buffer_gameover;


	alt_up_char_buffer_clear(char_buffer);

	audio_buffer_gameover = load_audio(9);

	tracker_l=22;
	tracker_r=22;
	play_once(audio_buffer_gameover,audio,9);
	alt_up_char_buffer_string(char_buffer, "GAME OVER!", 36, 8);
	alt_up_char_buffer_string(char_buffer, "ALL YOUR BASE ARE BELONG TO US", 25, 34);
	alt_up_char_buffer_string(char_buffer, "PRESS A TO RETURN TO MAIN MENU", 25, 38);


	while(enter_check < 2){

		decode_scancode(ps2_kb, &decode_mode, &data, &ascii);
		if(data == A_KEY){
			enter_check++;
		}
	}

	free(audio_buffer_gameover);
	alt_up_char_buffer_clear(char_buffer);

}



void level1_victory(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev * char_buffer, alt_up_ps2_dev * ps2_kb, KB_CODE_TYPE decode_mode,alt_u8 data, char ascii){

	int spacebar_detected = 0;

	alt_up_char_buffer_clear(char_buffer);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 0, 320, 240, 0x0A00, 0);

	while(spacebar_detected < 2){
		// display graphic
		alt_up_char_buffer_string(char_buffer, "CONGRATULATIONS!", 20, 20);
		alt_up_char_buffer_string(char_buffer, "YOU'VE DEFEATED THE SHARKS!", 20, 23);

		alt_up_char_buffer_string(char_buffer, "YOU'VE UNLOCKED TOWER 5, 6, 7 and 8!", 20, 25);
		draw_tower(pixel_buffer, 80, 125, 5);
		draw_tower(pixel_buffer, 110, 125, 6);
		draw_tower(pixel_buffer, 140, 125, 7);
		draw_tower(pixel_buffer, 170, 125, 8);

		alt_up_char_buffer_string(char_buffer, "Press SPACEBAR to continue", 40, 50);
		if(decode_scancode(ps2_kb, &decode_mode, &data, &ascii)== 0){
			if(data == SPACEBAR){
				spacebar_detected++;
			}
		}
	}
}

void level2_victory(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev * char_buffer, alt_up_ps2_dev * ps2_kb, KB_CODE_TYPE decode_mode,alt_u8 data, char ascii){

	int spacebar_detected = 0;

	alt_up_char_buffer_clear(char_buffer);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 0, 320, 240, 0x0A00, 0);

	while(spacebar_detected < 2){
		// display graphic
		alt_up_char_buffer_string(char_buffer, "CONGRATULATIONS!", 20, 20);
		alt_up_char_buffer_string(char_buffer, "YOU'VE DEFEATED THE SHARKS!", 20, 22);

		alt_up_char_buffer_string(char_buffer, "YOU'VE UNLOCKED TOWER 7 and 8", 20, 25);
		alt_up_char_buffer_string(char_buffer, "INSERT TOWER GRAPHICS HERE", 20, 28);
		alt_up_char_buffer_string(char_buffer, "Press SPACEBAR to continue", 40, 50);
		if(decode_scancode(ps2_kb, &decode_mode, &data, &ascii)== 0){
			if(data == SPACEBAR){
				spacebar_detected++;
			}
		}
	}
}


void freeEverything(dataPtr data){

	int i = 0;
	enePtr ene;
	enePtr eneTemp;
	towPtr tow;
	bulPtr bul;
	bulPtr bulTemp;

	//free enemies
	for(i = 0; i < NUMROW; i++){

		eneTemp = data->eneHead[i];

		while(eneTemp != NULL){
			data->eneHead[i] = eneTemp->next;
			free(eneTemp);
			eneTemp = data->eneHead[i];
		}
	}

	//free bullets, then the tower
	for(i = 0; i < NUMTOW; i++){

		tow = data->towers[i];
		bulTemp = tow->bulHead;


		while(bulTemp != NULL){
			tow->bulHead = bulTemp->next;
			free(bulTemp);
			bulTemp = tow->bulHead;
		}
		free(tow);
	}



}


void draw_tower(alt_up_pixel_buffer_dma_dev* pixel_buffer, int x_start, int y_start, int type) {
	int i, j;
	int pos = 0;

	switch(type) {
	case 1:
		for(i = 0; i < 30; i++) {
			for(j = 0; j < 25; j++) {
				if(cow_bmp[pos] != BLACK) {
					alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_start + j, y_start + i, x_start + j, y_start + i, cow_bmp[pos], 0);
				}
				pos++;
			}
		}
		break;
	case 2:
		for(i = 0; i < 30; i++) {
			for(j = 0; j < 25; j++) {
				if(baby_bmp[pos] != BLACK) {
					alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_start + j, y_start + i, x_start + j, y_start + i, baby_bmp[pos], 0);
				}
				pos++;
			}
		}
		break;
	case 3:
		for(i = 0; i < 30; i++) {
			for(j = 0; j < 25; j++) {
				if(baby_bmp[pos] != BLACK) {
					if(baby_bmp[pos] == 0x738E){
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_start + j, y_start + i, x_start + j, y_start + i, 0xFFE0, 0);
					}
					else if(baby_bmp[pos] == 0xD2CB){
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_start + j, y_start + i, x_start + j, y_start + i, 0xFFD0, 0);
					}
					else {
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_start + j, y_start + i, x_start + j, y_start + i, baby_bmp[pos], 0);
					}
				}
				pos++;


			}
		}
		break;
	case 4:
		for(i = 0; i < 30; i++) {
			for(j = 0; j < 25; j++) {
				if(baby_bmp[pos] != BLACK) {
					if(baby_bmp[pos] == 0x738E){
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_start + j, y_start + i, x_start + j, y_start + i, 0x0888, 0);
					}
					else if(baby_bmp[pos] == 0xD2CB){
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_start + j, y_start + i, x_start + j, y_start + i, 0xBDF7, 0);
					}
					else {
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_start + j, y_start + i, x_start + j, y_start + i, baby_bmp[pos], 0);
					}
				}

				pos++;
			}

		}
		break;
	case 5:
		for(i = 0; i < 30; i++)
		{
			for(j = 0; j < 25; j++){

				if(mine_bmp[pos]!= BLACK){
					alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_start+j, y_start+i,x_start+j, y_start+i, mine_bmp[pos], 0);

				}
				pos++;
			}


		}



						break;

	case 6:
		for(i = 0; i < 30; i++) {
			for(j = 0; j < 25; j++) {
				if(baby_bmp[pos] != BLACK) {
					if(baby_bmp[pos] == 0x738E){
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_start + j, y_start + i, x_start + j, y_start + i, 0x2FF, 0);
					}
					else if(baby_bmp[pos] == 0xD2CB){
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_start + j, y_start + i, x_start + j, y_start + i, 0x0E, 0);
					}
					else {
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_start + j, y_start + i, x_start + j, y_start + i, baby_bmp[pos], 0);
					}
				}

			pos++;
			}

		}
		break;

	case 7:
		for(i = 0; i < 30; i++) {
			for(j = 0; j < 25; j++) {
				if(baby_bmp[pos] != BLACK) {
					if(baby_bmp[pos] == 0x738E){
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_start + j, y_start + i, x_start + j, y_start + i, 0xF00F, 0);
					}
					else if(baby_bmp[pos] == 0xD2CB){
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_start + j, y_start + i, x_start + j, y_start + i, 0xF00A, 0);
					}
					else {
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_start + j, y_start + i, x_start + j, y_start + i, baby_bmp[pos], 0);
					}
				}

				pos++;
			}
		}
		break;
	case 8:
		for(i = 0; i < 30; i++) {
			for(j = 0; j < 25; j++) {
				if(baby_bmp[pos] != BLACK) {
					if(baby_bmp[pos] == 0x738E){
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_start + j, y_start + i, x_start + j, y_start + i, 0x0001, 0);
					}
					else if(baby_bmp[pos] == 0xD2CB){
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_start + j, y_start + i, x_start + j, y_start + i, 0xBDF7, 0);
					}
					else {
						alt_up_pixel_buffer_dma_draw_box(pixel_buffer, x_start + j, y_start + i, x_start + j, y_start + i, baby_bmp[pos], 0);
					}
				}

				pos++;
			}
		}
		break;
	}
}





