#include <stdio.h>
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"

#include "title_screen.h"
#include "graphics.h"
#include "game_structs.h"
#include "tower_select.h"
#include "background_graphics.h"
#include "heads_up_display.h"
#include "keyboard_codes.h"
extern alt_up_pixel_buffer_dma_dev* pixel_buffer;


void tower_selection(alt_up_ps2_dev *ps2_kb, KB_CODE_TYPE decode_mode, alt_u8 data, char ascii, int temp_baby[]){
	int tower;


	//temp_baby[0] = colour WILL BE COST IN FUTURE
	//temp_baby[1] = health
	//temp_baby[2] = bullet type
	//temp_baby[3] = to/baseAttack

		if(data == ONE_KEY){  //if user presses 1 : Dairy Cow (Resource Generator)

			temp_baby[0] = 0x0000; //5
			temp_baby[1] = 9;
			temp_baby[2] = 1;
			temp_baby[3] = 400;
			tower = 1;


		}

		else if(data == TWO_KEY){  //if user presses 2 : Infant-ry (Normal Tower)

			temp_baby[0] = 0x000F; //7
			temp_baby[1] = 15; //health
			temp_baby[2] = 2;  //bullet type
			temp_baby[3] = 20;  //toAttack/baseAttack
			tower = 2;


		}

		else if(data == THREE_KEY){  //if user presses 3 : Rapid-fire Rugrat (Rapid-Fire Tower)

			temp_baby[0] = 0x00F0;  //10
			temp_baby[1] = 15;
			temp_baby[2] = 3;
			temp_baby[3] = 10;
			tower = 2;

		}

		else if(data == FOUR_KEY){  //if user presses 4 :  (Defensive Tower)

			temp_baby[0] = 0x0F00;  //10
			temp_baby[1] = 30;
			temp_baby[2] = 4;
			temp_baby[3] = 0;
			tower = 3;

		}


		else if(data == FIVE_KEY){  //if user presses 5 : (Mine Tower)

			temp_baby[0] = 0xF000;  //7
			temp_baby[1] = 5;
			temp_baby[2] = 5;
			temp_baby[3] = 200;
			tower = 4;

		}


		else if(data == SIX_KEY){  //if user presses 6 : (Ice Tower)

			temp_baby[0] = 0xFF00;  //13
			temp_baby[1] = 11;
			temp_baby[2] = 6;
			temp_baby[3] = 30;
			tower = 5;

		}


		else if(data == SEVEN_KEY){  //if user presses 7 :  (Poison Tower)

			temp_baby[0] = 0x0FF0;  //13
			temp_baby[1] = 11;
			temp_baby[2] = 7;
			temp_baby[3] = 20;
			tower = 6;

		}

		else if(data == EIGHT_KEY){  //if user presses 8 : (Rocket Tower)

			temp_baby[0] = 0x00FF; //15
			temp_baby[1] = 22;
			temp_baby[2] = 8;
			temp_baby[3] = 30;
			tower = 7;

		}

		//tower_indicator(tower, pixel_buffer);

}


void remove_baby(Tower* baby, int grid, alt_up_pixel_buffer_dma_dev* pixel_buffer){
	int i;
	int color_inc = 0x0001;

	baby->isAlive = 0;

	if(grid<=6){
		for(i = 46; i < 84; i++) {
			alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 15+((6 - grid)*40), 53+((6 - grid)*40), i, BLACK + color_inc, 0);
			if(i % 8 == 0) color_inc++;
		}
	}
	else if(grid > 6){
		for(i = 86; i < 124; i++) {
			alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 15+((13-grid)*40), 53+((13 - grid)*40), i, BLACK + (38+color_inc), 0);
			if(i % 8 == 0) color_inc++;
		}

	}


}
