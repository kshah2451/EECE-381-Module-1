#include <stdio.h>
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"

#include "title_screen.h"
#include "graphics.h"
#include "game_structs.h"
#include "keyboard_codes.h"
#include "audio.h"
extern alt_up_pixel_buffer_dma_dev* pixel_buffer;

extern alt_up_audio_dev* audio;
extern unsigned int *audio_buffer_title;

int move_title_cursor(int cursor_x, int cursor_y, alt_up_ps2_dev * ps2_kb, KB_CODE_TYPE decode_mode,alt_u8 data, char ascii);
/*Title Screen code*/
int title_screen(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev * char_buffer, int start, alt_up_ps2_dev * ps2_kb, KB_CODE_TYPE decode_mode,alt_u8 data, char ascii)


{
	int j,k;
	int enter_pressed = 0;
	int cursor_x = 130;
	int cursor_y = 140;
	int move_cursor = 0;

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

	// Write some text
	alt_up_char_buffer_string(char_buffer, "Sharks VS Babies", 32, 32);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, cursor_x, cursor_y, cursor_x+60, cursor_y + 10, 0x0FFF, 0);

	audio = alt_up_audio_open_dev("/dev/audio_0");
	while(enter_pressed < 2){ //wait for user to press start

		//PLAY MUSIC HERE=
		play_loop(audio_buffer_title,audio,0);

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
