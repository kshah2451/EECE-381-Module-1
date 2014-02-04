#ifndef HEADS_UP_DISPLAY_H_
#define HEADS_UP_DISPLAY_H_

#include <stdio.h>

#include "graphics.h"
#include "altera_up_ps2_keyboard.h"
#include "altera_up_avalon_ps2.h"
#include "altera_up_avalon_ps2_regs.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"

#define BLACK 0x0000
#define WHITE 0xFFFF
#define RED 0xF800
#define D_BLUE 0x1B
#define L_BLUE 0xDFF
#define BLUE 0x1F
#define GREEN 0x7E0
#define YELLOW 0xFFE0
#define BROWN 0x7FE0
#define BEIGE 0xFE99
#define ORANGE 0xFBE0

void heads_up_display_static(void); //draws the display which is unchanging
void heads_up_display_dynamic(int,int,alt_up_char_buffer_dev*,char*); //draws parts of the display which are changing
void tower_indicator(int, alt_up_pixel_buffer_dma_dev*);//draws rectangle indicating choice of tower

#endif /* HEADS_UP_DISPLAY_H_ */
