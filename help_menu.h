/*
 * help_menu.h
 *
 *  Created on: Feb 9, 2014
 *      Author: Keval
 */
#ifndef HELP_MENU_H_
#define HELP_MENU_H_

#include "altera_up_ps2_keyboard.h"
#include "altera_up_avalon_ps2.h"
#include "altera_up_avalon_ps2_regs.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"

#include "Colors.h"
#include "keyboard_codes.h"

#define HOW_TO_PLAY_MENU 0
#define TOWERS_MENU 1
#define SHARKS_MENU 2
#define CONTROLS_MENU 3
#define DEVS_MENU 4


void draw_help_menu(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev* char_buffer, alt_up_ps2_dev *ps2_kb, KB_CODE_TYPE  decode_mode);

void draw_current_menu(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev* char_buffer, int current_menu);

void draw_menu_text(alt_up_char_buffer_dev* char_buffer);

void clear_menu_text(alt_up_char_buffer_dev* char_buffer);

void draw_how_to_play_guide(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev* char_buffer);

void draw_towers_guide(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev* char_buffer);

void draw_sharks_guide(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev* char_buffer);

void draw_controls_guide(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev* char_buffer);

void draw_developers_guide(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev* char_buffer);

#endif /* HELP_MENU_H_ */
