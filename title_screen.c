#include <stdio.h>
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"

#include "title_screen.h"
#include "graphics.h"
#include "game_structs.h"
#include "keyboard_codes.h"
#include "audio.h"
#include "bitmaps.h"
#include "Colors.h"
extern alt_up_pixel_buffer_dma_dev* pixel_buffer;

extern alt_up_audio_dev* audio;
extern unsigned int *audio_buffer_title;

int move_title_cursor(int cursor_x, int cursor_y, alt_up_ps2_dev * ps2_kb, KB_CODE_TYPE decode_mode,alt_u8 data, char ascii);
/*Title Screen code*/
int title_screen(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev * char_buffer, int start, alt_up_ps2_dev * ps2_kb, KB_CODE_TYPE decode_mode,alt_u8 data, char ascii)


{
	int i,j,k;
	int enter_pressed = 0;
	int cursor_x = 130;
	int cursor_y = 140;
	int move_cursor = 0;
	int pixel_el = 0;

	alt_up_char_buffer_clear(char_buffer);
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);



	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 60, 320, 120, 0x0099, 0);

	for(i = 0; i < 30; i++)
	{
		for(j = 0; j < 25; j++){

			if(cow_bmp[pixel_el]!= BLACK){
				alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 90+j, 80+i,90+j, 80+i, cow_bmp[pixel_el], 0);

			}
			pixel_el++;
		}


	}

	pixel_el = 0;
	for(i = 0; i < 30; i++)
	{
		for(j = 0; j < 25; j++){

			if(baby_bmp[pixel_el]!= BLACK){
				alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 110+j, 80+i,110+j, 80+i, baby_bmp[pixel_el],

0);

			}
			pixel_el++;
		}


	}
	/**Shark Image**/
	draw_sharkfin(pixel_buffer, 208, 58, 0x0ff0);

	draw_sharkfin(pixel_buffer, 240, 59, 0x00ff);
	draw_sharkfin(pixel_buffer, 224, 74, 0x0000);
	draw_sharkfin(pixel_buffer, 240, 84, 0x7bef);


	draw_sharkfin(pixel_buffer, 188, 74, 0x7bef);
	draw_sharkfin(pixel_buffer, 208, 85, 0xffff);

	// Write some text
	alt_up_char_buffer_string(char_buffer, "Sharks VS Babies", 32, 32);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, cursor_x, cursor_y, cursor_x+60, cursor_y + 10, 0x0FFF, 0);

	audio = alt_up_audio_open_dev("/dev/audio_0");
	while(enter_pressed < 2){ //wait for user to press start

		//PLAY MUSIC HERE=
		play_loop(audio_buffer_title,audio,0);//plays samples repeatedly until the user chooses to start, thus exitting the while loop

		alt_up_char_buffer_string(char_buffer, "New Game", 35, 36);
		alt_up_char_buffer_string(char_buffer, "Load Game", 35, 39);
		alt_up_char_buffer_string(char_buffer, "How to Play", 34, 42);



		alt_up_char_buffer_string(char_buffer, "ALL RIGHTS RESERVED", 30, 48);
		alt_up_char_buffer_string(char_buffer, "COPYRIGHT 2013    FACULTY OF ARTS SOFTWARE", 20, 50);
		alt_up_char_buffer_string(char_buffer, "LICENSED BY EECE 381", 30, 52);


		if (decode_scancode(ps2_kb, &decode_mode, &data, &ascii)==0){

			if(data == DOWN || data == UP){
				move_cursor++;
			}

			else if (data == ENTER){
				enter_pressed++;
			}


			if(move_cursor >= 2){
				cursor_y = move_title_cursor(cursor_x, cursor_y, ps2_kb, decode_mode, data, ascii);
				move_cursor = 0;
			}


		}

	}
	free(audio_buffer_title);

	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
	alt_up_char_buffer_clear(char_buffer);


		if (cursor_y == NEWGAME)
			return 1;
		else if (cursor_y == LOADGAME){
			return 2;
		}
		else if(cursor_y == HOWTOPLAY){
			return 3;
		}


return 0;
}

int move_title_cursor(int cursor_x, int cursor_y,alt_up_ps2_dev * ps2_kb, KB_CODE_TYPE decode_mode,alt_u8 data, char ascii){

		if(cursor_y == 140){
			if(data == DOWN){
				alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, cursor_x, cursor_y, cursor_x+60, cursor_y + 10, 0x0000, 0);
				cursor_y += 12;
				alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, cursor_x, cursor_y, cursor_x+60, cursor_y + 10, 0x0FFF, 0);
			}
		}
		else if (cursor_y == 152){
			if(data == UP){
						alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, cursor_x, cursor_y, cursor_x+60, cursor_y + 10, 0x0000, 0);
						cursor_y -= 12;
						alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, cursor_x, cursor_y, cursor_x+60, cursor_y + 10, 0x0FFF, 0);
					}
			else if(data == DOWN){
				alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, cursor_x, cursor_y, cursor_x+60, cursor_y + 10, 0x0000, 0);
				cursor_y += 12;
				alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, cursor_x, cursor_y, cursor_x+60, cursor_y + 10, 0x0FFF, 0);
			}

		}

		else if (cursor_y == 164){
			if(data == UP){
						alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, cursor_x, cursor_y, cursor_x+60, cursor_y + 10, 0x0000, 0);
						cursor_y -= 12;
						alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, cursor_x, cursor_y, cursor_x+60, cursor_y + 10, 0x0FFF, 0);
					}
		}


	return cursor_y;


}
