#include <stdio.h>
#include "altera_up_ps2_keyboard.h"
#include "altera_up_avalon_ps2.h"
#include "altera_up_avalon_ps2_regs.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"
#include "game_structs.h"
#include "graphics.h"
#include "title_screen.h"
#include "cursor.h"


/*main gameplay cursor logic with some vga that might need to be removed when we put everything together*/
void move_cursor()
{
	KB_CODE_TYPE decode_mode;
	alt_u8 data;
	char ascii;
	char *p;
	int start = 0;
	int grid_pos = 1;

	alt_up_ps2_dev *ps2_kb;
	ps2_kb=alt_up_ps2_open_dev("/dev/ps2");
	alt_up_ps2_init(ps2_kb);
	alt_up_ps2_clear_fifo(ps2_kb);

	alt_up_pixel_buffer_dma_dev* pixel_buffer;
	pixel_buffer =
	  alt_up_pixel_buffer_dma_open_dev("/dev/pixel_buffer_dma");

	// Set the background buffer address – Although we don’t use the
	//background, // they only provide a function to change the background
	//buffer address, so
	// we must set that, and then swap it to the foreground.
	alt_up_pixel_buffer_dma_change_back_buffer_address(pixel_buffer,
	PIXEL_BUFFER_BASE);

	// Swap background and foreground buffers
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);

	// Wait for the swap to complete
	while
	(alt_up_pixel_buffer_dma_check_swap_buffers_status(pixel_buffer));

	// Initialize the character buffer
	alt_up_char_buffer_dev *char_buffer;
	char_buffer = alt_up_char_buffer_open_dev("/dev/char_drawer");
	alt_up_char_buffer_init(char_buffer);

	//clear pixel buffer memory
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);

	//set background image
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, BG_UPPER_X, BG_UPPER_Y, BG_LOWER_X, BG_LOWER_Y, SEA_COLOUR, 0);

	initialize_cursor(grid_pos, CURSOR_COLOUR);
	draw_cursor(cur.pos,cur.colour, pixel_buffer);

	/*main cursor logic loop. Will keep scanning keyboard inputs, and will upgrade 
	  grid values accordingly*/
	while(1)
	 {
		if (decode_scancode(ps2_kb, &decode_mode, &data, &ascii)==0)
		{

			if(cur.pos[0] == BG_UPPER_X && cur.pos[1] == BG_UPPER_Y){
				//if cursor can't go left or up
				if(data == 0x72){ //down
					grid_pos = (MAX_GRIDS/2)+grid_pos;
					initialize_cursor(grid_pos, CURSOR_COLOUR);

					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

				}
				else if(data == 0x74){ //right
					grid_pos = grid_pos + 1;
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

				}
			}

			else if(cur.pos[1] == BG_UPPER_Y && cur.pos[2] == BG_LOWER_X){
				//if cursor can't go right or up
				if(data == 0x72){ //down
					grid_pos = (MAX_GRIDS/2)+grid_pos;
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

				}
				else if(data == 0x6b){ //left
					grid_pos = grid_pos - 1;
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

				}


			}
			else if(cur.pos[3] == BG_LOWER_Y && cur.pos[2] == BG_LOWER_X){
				//if cursor can't go down or right
				if(data == 0x75){ //up
					grid_pos = grid_pos - (MAX_GRIDS/2);
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);
				}

				else if(data == 0x6b){ //left
					grid_pos = grid_pos - 1;
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

				}


			}


			else if(cur.pos[0] == BG_UPPER_X && cur.pos[3] == BG_LOWER_Y){
				//if cursor can't go left or down

				if(data == 0x75){ //up
					grid_pos = grid_pos - (MAX_GRIDS/2);
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);
				}
				else if(data == 0x74){ //right
					grid_pos = grid_pos + 1;
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

				}


			}

			else if(cur.pos[1] == BG_UPPER_Y){
				//if cursor can't go up
				if(data == 0x72){ //down
					grid_pos = (MAX_GRIDS/2)+grid_pos;
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

				}
				else if(data == 0x74){ //right
					grid_pos = grid_pos + 1;
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

				}
				else if(data == 0x6b){ //left
					grid_pos = grid_pos - 1;
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

				}


			}



			else if(cur.pos[3] == BG_LOWER_Y){
				//if cursor can't go down
				if(data == 0x75)
				{ //up
					grid_pos = grid_pos - (MAX_GRIDS/2);
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);
				}
				else if(data == 0x74){ //right
					grid_pos = grid_pos + 1;
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

				}
				else if(data == 0x6b){ //left
					grid_pos = grid_pos - 1;
					initialize_cursor(grid_pos, CURSOR_COLOUR);
					draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);

				}


			}


			}

		 }


}