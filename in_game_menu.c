#include "in_game_menu.h"


void switch_to_menu(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev* char_buffer, alt_up_ps2_dev *ps2_kb, KB_CODE_TYPE  decode_mode) {
	int count = 0;
	int exit_flag = 0;
	int item = RESUME;
	alt_u8 data;
	char ascii;
	//draw_in_game_menu(pixel_buffer, char_buffer);
	alt_irq_disable(TIMER_0_IRQ);
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	while(exit_flag == 0) {
		draw_in_game_menu(pixel_buffer, char_buffer);
		draw_rectangle(pixel_buffer, RESUME);
		item = RESUME;
		while(1)
		{
			if (decode_scancode(ps2_kb, &decode_mode, &data, &ascii) == 0) {
				if(data == UP || data == DOWN) count++;
				if(data == UP && count >= 2) {
					clear_rectangle(pixel_buffer, item);
					if(item != RESUME) item--;
					draw_rectangle(pixel_buffer, item);
					count = 0;
				}
				if(data == DOWN && count >= 2) {
					clear_rectangle(pixel_buffer, item);
					if(item != QUIT) item++;
					draw_rectangle(pixel_buffer, item);
					count = 0;
				}
				if(data == ENTER) {
					if(item == RESUME) {
						exit_flag = 1;
						break;
					}
					else if(item == SAVE_GAME) {
						// ADD CODE TO SAVE GAME
					}
					else if(item == HELP) {
						draw_help_menu(pixel_buffer, char_buffer, ps2_kb, decode_mode);
						break;
					}
					else if(item == QUIT) {
						// ADD CODE TO QUIT GAME AND GO TO TITLE SCREEN
					}
				}
			}
		}
	}
	alt_up_pixel_buffer_dma_clear_screen(pixel_buffer, 0);
	clear_in_game_menu_text(char_buffer);
	alt_up_pixel_buffer_dma_swap_buffers(pixel_buffer);
	alt_irq_enable(TIMER_0_IRQ);
}


void draw_in_game_menu(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev* char_buffer) {
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 107, 10, 214, 230, RED, 0);
	alt_up_char_buffer_string(char_buffer, "PAUSED", 37, 5);
	alt_up_char_buffer_string(char_buffer, "RESUME", 37, 15);
	alt_up_char_buffer_string(char_buffer, "SAVE  GAME", 35, 20);
	alt_up_char_buffer_string(char_buffer, "HELP", 38, 25);
	alt_up_char_buffer_string(char_buffer, "QUIT", 38, 30);
}

void clear_in_game_menu_text(alt_up_char_buffer_dev* char_buffer) {
	alt_up_char_buffer_string(char_buffer, "      ", 37, 5);
	alt_up_char_buffer_string(char_buffer, "      ", 37, 15);
	alt_up_char_buffer_string(char_buffer, "          ", 35, 20);
	alt_up_char_buffer_string(char_buffer, "    ", 38, 25);
	alt_up_char_buffer_string(char_buffer, "    ", 38, 30);
}

void draw_rectangle(alt_up_pixel_buffer_dma_dev* pixel_buffer, int text_position) {
	switch(text_position) {
	case RESUME:
		alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 130, 55, 190, 68, YELLOW, 0);
		break;
	case SAVE_GAME:
		alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 130, 75, 190, 88, YELLOW, 0);
		break;
	case HELP:
		alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 130, 95, 190, 108, YELLOW, 0);
		break;
	case QUIT:
		alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 130, 115, 190, 128, YELLOW, 0);
		break;
	}
}

void clear_rectangle(alt_up_pixel_buffer_dma_dev* pixel_buffer, int text_position) {
	switch(text_position) {
		case RESUME:
			alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 130, 55, 190, 68, BLACK, 0);
			break;
		case SAVE_GAME:
			alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 130, 75, 190, 88, BLACK, 0);
			break;
		case HELP:
			alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 130, 95, 190, 108, BLACK, 0);
			break;
		case QUIT:
			alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, 130, 115, 190, 128, BLACK, 0);
			break;
	}
}


