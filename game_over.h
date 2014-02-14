#ifndef GAME_OVER_H_
#define HEADS_UP_DISPLAY_H_

#include <stdio.h>

#include "graphics.h"
#include "altera_up_ps2_keyboard.h"
#include "altera_up_avalon_ps2.h"
#include "altera_up_avalon_ps2_regs.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"
#include "keyboard_codes.h"
#include "bitmaps.h"

#define BLACK 0x0000
#define WHITE 0xFFFF
#define RED 0xF800
#define LV1VICTORY 1000

void victory(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev * char_buffer, alt_up_ps2_dev *ps2_kb, KB_CODE_TYPE decode_mode, alt_u8 data, char ascii);

void gameover(alt_up_pixel_buffer_dma_dev*,alt_up_char_buffer_dev*, alt_up_ps2_dev *ps2_kb, KB_CODE_TYPE decode_mode, alt_u8 data, char ascii);

void level1_victory(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev * char_buffer, alt_up_ps2_dev * ps2_kb, KB_CODE_TYPE decode_mode,alt_u8 data, char ascii);

void level2_victory(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev * char_buffer, alt_up_ps2_dev * ps2_kb, KB_CODE_TYPE decode_mode,alt_u8 data, char ascii);

void freeEverything(dataPtr data);

void draw_tower(alt_up_pixel_buffer_dma_dev* pixel_buffer, int x_start, int y_start, int type);

#endif /* HEADS_UP_DISPLAY_H_ */
