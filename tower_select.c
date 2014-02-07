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

		if(data == ONE_KEY){  //if user presses 1 : Dairy Cow (Resource Generator)

			temp_baby[0] = 0xF000; //black
			temp_baby[1] = 50;
			temp_baby[2] = 0;
			temp_baby[3] = 1;
			tower = 0;


		}

		else if(data == TWO_KEY){  //if user presses 2 : Infant-ry

			temp_baby[0] = 0xFE99;
			temp_baby[1] = 100; //health
			temp_baby[2] = 1;  //bullet type
			temp_baby[3] = 1;  //toAttack/baseAttack
			tower = 1;


		}

		else if(data == THREE_KEY){  //if user presses 3 : Rapid-fire Rugrat

			temp_baby[0] = 0xFFE0;
			temp_baby[1] = 50;
			temp_baby[2] = 2;
			temp_baby[3] = 1;
			tower = 2;

		}
		tower_indicator(tower, pixel_buffer);

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

