#ifndef IN_GAME_MENU_H_
#define IN_GAME_MENU_H_

#include "altera_up_ps2_keyboard.h"
#include "altera_up_avalon_ps2.h"
#include "altera_up_avalon_ps2_regs.h"
#include <sys/alt_irq.h>
#include <altera_avalon_timer_regs.h>

#include "graphics.h"
#include "keyboard_codes.h"
#include "Colors.h"

#define RESUME 0
#define SAVE_GAME 1
#define HELP 2
#define QUIT 3

void switch_to_menu(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev* char_buffer, alt_up_ps2_dev *ps2_kb, KB_CODE_TYPE decode_mode);

void draw_in_game_menu(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev* char_buffer);

void clear_menu_text(alt_up_char_buffer_dev* char_buffer);

void clear_rectangle(alt_up_pixel_buffer_dma_dev* pixel_buffer, int text_position);

void draw_rectangle(alt_up_pixel_buffer_dma_dev* pixel_buffer, int text_position);

void draw_help_menu(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev* char_buffer, alt_up_ps2_dev *ps2_kb, KB_CODE_TYPE  decode_mode);

#endif
