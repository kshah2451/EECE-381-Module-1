#ifndef HEADS_UP_DISPLAY_H_
#define HEADS_UP_DISPLAY_H_

#include <stdio.h>
#include <stdlib.h>

#include "altera_up_ps2_keyboard.h"
#include "altera_up_avalon_ps2.h"
#include "altera_up_avalon_ps2_regs.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"

#include "Colors.h"

void heads_up_display_static(alt_up_pixel_buffer_dma_dev*, alt_up_char_buffer_dev*); //draws the display which is unchanging
void heads_up_display_dynamic(int,int,alt_up_char_buffer_dev*,char*); //draws parts of the display which are changing
void tower_indicator(int, alt_up_pixel_buffer_dma_dev*);//draws rectangle indicating choice of tower
void display_health(int health );
void clear_all_selection(alt_up_pixel_buffer_dma_dev* pixel_buffer);

#endif /* HEADS_UP_DISPLAY_H_ */
