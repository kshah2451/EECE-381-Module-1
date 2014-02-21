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
#include "game_over.h"
#include "level_one.h"
#include "level_two.h"
#include "story_seq.h"
#include "save_game.h"
#include "audio.h"
#include "read_image.h"
#include "help_menu.h"


//GLOBAL VARIABLES
alt_up_pixel_buffer_dma_dev* pixel_buffer;
alt_up_char_buffer_dev* char_buffer;

int gameOverFlag = 0;
int victoryFlag = 0;
int maxEnemy = 0;
int resources = 0;
int levelThreeFlag = 0;
int levelFlag = 1;



unsigned int tracker_l = 22; //keeps track of position in audio file for the left buffer
unsigned int tracker_r = 22; //keeps track of position in audio file for the right buffer

int level = 1;

alt_up_audio_dev * audio = NULL;
unsigned int *audio_buffer_title;//array to hold title screen background music
/*main gameplay cursor logic, with some title screen features .. will have to seperate*/
int main()
{

	unsigned int* picture;
	//picture = read_image();
	audio_buffer_title = load_audio(0); //loads title screen music

	KB_CODE_TYPE decode_mode;
	alt_u8 data;
	char ascii;
	char *p;
	int start = 0;		//i dont think im actually using this... will have to check
	int num_babies = 0; //i dont think im actually using this... will have to check
	int i;
	int menu_selection; // 1: New Game   2:Load Game   3: How to Play
/*	dataPtr game_data = (dataPtr)malloc(sizeof(gameData));
	for(i = 0; i < NUMROW; i++){
		game_data->eneHead[i] = NULL;
	}*/


				/* HAL INITIALIZATIONS*/



/*	// set positions of baby towers
	set_baby_positions(game_data->towers);*/

	//bunch of keyboard initializations
	alt_up_ps2_dev *ps2_kb;
	ps2_kb=alt_up_ps2_open_dev("/dev/ps2");
	alt_up_ps2_init(ps2_kb);
	alt_up_ps2_clear_fifo(ps2_kb);

	//pixel buffer initializations

	// Use the name of your pixel buffer DMA core
	pixel_buffer = alt_up_pixel_buffer_dma_open_dev("/dev/pixel_buffer_dma");

	unsigned int pixel_buffer_addr1 = PIXEL_BUFFER_BASE;
	unsigned int pixel_buffer_addr2 = PIXEL_BUFFER_BASE + (320 * 240 * 2);

	// Set the 1st buffer address
	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer,
	 pixel_buffer_addr1);

	// Swap buffers  we have to swap because there is only an API function
	// to set the address of the background buffer.
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	while (alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer))
	 ;

	// Set the 2nd buffer address
	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer,
	 pixel_buffer_addr2);

	// Clear both buffers (this makes all pixels black)
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 1);

	// Initialize the character buffer
	char_buffer = alt_up_char_buffer_open_dev("/dev/char_drawer");
	alt_up_char_buffer_init(char_buffer);

	//clear pixel buffer memory
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);

	int j,k,x;
	x=0;
	for(j=0;j<240;j++){
		for(k=0;k<320;k++){
			alt_up_pixel_buffer_dma_draw_box(pixel_buffer,k,j,k,j,*(picture+x),0);
			x++;
		}

	}
						/*MAIN GAME*/
	while(1){

		//save_level('2');
						/* TITLE SCREEN*/
					// display the title screen
		level = 1;
		data = 0;
		menu_selection = title_screen(pixel_buffer, char_buffer, start, ps2_kb, decode_mode, data, ascii); //wait here until "ENTER"
		alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);

		if(menu_selection == 2){ //Load Game
			victory(pixel_buffer, char_buffer, ps2_kb, decode_mode, data, ascii);
			//level = load_save()-'0';
		}
		else if(menu_selection == 3){ // How to Play
			//victory(pixel_buffer, char_buffer, ps2_kb, decode_mode, data, ascii);
			draw_help_menu(pixel_buffer,char_buffer,ps2_kb,decode_mode);
		}
		if (menu_selection == 1){ // New Game
			/*LEVEL ONE*/
			pre_level_story_1(pixel_buffer, char_buffer,ps2_kb, decode_mode,data, ascii);
			if(level == 1){
				mainGame_level1(ps2_kb, decode_mode, data, ascii);
				level++;
			}
			if(gameOverFlag == 1){  //Lv1 Game Over
				gameover(pixel_buffer,char_buffer, ps2_kb, decode_mode, data, ascii);
				gameOverFlag = 0;
				victoryFlag = 0;
			}
			else if(victoryFlag >= LV1VICTORY){ // Level 1 Victory
				gameOverFlag = 0;
				victoryFlag = 0;
				level1_victory(pixel_buffer, char_buffer,ps2_kb, decode_mode,data, ascii);
				alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);

				/*LEVEL TWO*/
				//replace this with level 2
				levelFlag = 2;
				pre_level_story_2(pixel_buffer, char_buffer,ps2_kb, decode_mode,data, ascii);
				mainGame_level2(ps2_kb, decode_mode, data, ascii);
				if(gameOverFlag == 1){  //Lv2 Game Over
					gameover(pixel_buffer,char_buffer, ps2_kb, decode_mode, data, ascii);
					gameOverFlag = 0;
					victoryFlag = 0;
					levelFlag = 1;
				}

				else if(victoryFlag >= 10){ //Lv2 Victory
					gameOverFlag = 0;
					victoryFlag = 0;
					levelFlag = 1;
					victory(pixel_buffer, char_buffer,ps2_kb, decode_mode,data, ascii);
					alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);

				}

			}
		}

	} //closes while


  return 0;
}




