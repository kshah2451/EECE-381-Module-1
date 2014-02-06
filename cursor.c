#include <stdio.h>
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"

#include "title_screen.h"
#include "graphics.h"
#include "game_structs.h"
#include "tower_select.h"
#include "cursor.h"
#include "keyboard_keys.h"

int move_cursor(int grid_pos, alt_up_ps2_dev *ps2_kb, KB_CODE_TYPE decode_mode, alt_u8 data, char ascii, alt_up_pixel_buffer_dma_dev* pixel_buffer){
	//if the cursor can't go left or up
	if(cur.pos[0] == BG_UPPER_X && cur.pos[1] == BG_UPPER_Y){

		if(data == DOWN){ // user presses down
			grid_pos = (NUMTOW/NUMROW)+grid_pos;
			set_cursor(grid_pos, CURSOR_COLOUR);

			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

		}
		else if(data == RIGHT){ //user presses right

			grid_pos = grid_pos - 1;
			set_cursor(grid_pos, CURSOR_COLOUR);
			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

		}
	}
	//if the cursor can't go right or up
	else if(cur.pos[1] == BG_UPPER_Y && cur.pos[2] == BG_LOWER_X){

		if(data == DOWN){ //user presses down
			grid_pos = (NUMTOW/NUMROW)+grid_pos;
			set_cursor(grid_pos, CURSOR_COLOUR);
			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

		}
		else if(data == LEFT){ //user presses left
			grid_pos = grid_pos + 1;
			set_cursor(grid_pos, CURSOR_COLOUR);
			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

		}


	}
	//if the cursor can't go down or right
	else if(cur.pos[3] == BG_LOWER_Y && cur.pos[2] == BG_LOWER_X){

		if(data == UP){ //user presses up
			grid_pos = grid_pos - (NUMTOW/NUMROW);
			set_cursor(grid_pos, CURSOR_COLOUR);
			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);
		}

		else if(data == LEFT){ //user presses left
			grid_pos = grid_pos + 1;
			set_cursor(grid_pos, CURSOR_COLOUR);
			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

		}


	}

	//if the cursor can't go left or down
	else if(cur.pos[0] == BG_UPPER_X && cur.pos[3] == BG_LOWER_Y){

		if(data == UP){ //user presses up
			grid_pos = grid_pos - (NUMTOW/NUMROW);
			set_cursor(grid_pos, CURSOR_COLOUR);
			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);
		}
		else if(data == RIGHT){ //right
			grid_pos = grid_pos - 1;
			set_cursor(grid_pos, CURSOR_COLOUR);
			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

		}


	}

	//if the cursor can't go up
	else if(cur.pos[1] == BG_UPPER_Y){
		if(data == DOWN){ //user presses down
			grid_pos = (NUMTOW/NUMROW)+grid_pos;
			set_cursor(grid_pos, CURSOR_COLOUR);
			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

		}
		else if(data == RIGHT){ //user presses right
			grid_pos = grid_pos - 1;
			set_cursor(grid_pos, CURSOR_COLOUR);
			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

		}
		else if(data == LEFT){ //user presses left
			grid_pos = grid_pos + 1;
			set_cursor(grid_pos, CURSOR_COLOUR);
			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

		}


	}
	//if the cursor can't go down
	else if(cur.pos[3] == BG_LOWER_Y){
		if(data == UP)
		{ //up
			grid_pos = grid_pos - (NUMTOW/NUMROW);
			set_cursor(grid_pos, CURSOR_COLOUR);
			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);
		}
		else if(data == RIGHT){ //right
			grid_pos = grid_pos - 1;
			set_cursor(grid_pos, CURSOR_COLOUR);
			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

		}
		else if(data == LEFT){ //left
			grid_pos = grid_pos + 1;
			set_cursor(grid_pos, CURSOR_COLOUR);
			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

		}
	}

	//can't go left
	else if(cur.pos[0] == BG_UPPER_X){
		if(data == UP)
		{ //up
			grid_pos = grid_pos - (NUMTOW/NUMROW);
			set_cursor(grid_pos, CURSOR_COLOUR);
			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);
		}
		else if(data == RIGHT){ //right
			grid_pos = grid_pos - 1;
			set_cursor(grid_pos, CURSOR_COLOUR);
			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

		}
		else if(data == DOWN){ //user presses down
			grid_pos = (NUMTOW/NUMROW)+grid_pos;
			set_cursor(grid_pos, CURSOR_COLOUR);
			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

		}
	}

	//can't go right
	else if(cur.pos[2] == BG_LOWER_X){
		if(data == UP)
		{ //up
			grid_pos = grid_pos - (NUMTOW/NUMROW);
			set_cursor(grid_pos, CURSOR_COLOUR);
			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);
		}
		else if(data == LEFT){ //left
			grid_pos = grid_pos + 1;
			set_cursor(grid_pos, CURSOR_COLOUR);
			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

		}
		else if(data == DOWN){ //user presses down
			grid_pos = (NUMTOW/NUMROW)+grid_pos;
			set_cursor(grid_pos, CURSOR_COLOUR);
			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

		}
	}

	else
		if(data == UP)
		{ //up
			grid_pos = grid_pos - (NUMTOW/NUMROW);
			set_cursor(grid_pos, CURSOR_COLOUR);
			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);
		}
		else if(data == LEFT){ //left
			grid_pos = grid_pos + 1;
			set_cursor(grid_pos, CURSOR_COLOUR);
			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

		}
		else if(data == DOWN){ //user presses down
			grid_pos = (NUMTOW/NUMROW)+grid_pos;
			set_cursor(grid_pos, CURSOR_COLOUR);
			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

		}
		else if(data == RIGHT){ //right
			grid_pos = grid_pos - 1;
			set_cursor(grid_pos, CURSOR_COLOUR);
			draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

		}




	return grid_pos;
}


