/*
 * title_screen.h
 *
 *  Created on: 2014-01-28
 *      Author: Cyril
 */

#ifndef TITLE_SCREEN_H_
#define TITLE_SCREEN_H_

#define NEWGAME 140
#define LOADGAME 152
#define HOWTOPLAY 164


#include <stdio.h>
#include "altera_up_ps2_keyboard.h"
#include "altera_up_avalon_ps2.h"
#include "altera_up_avalon_ps2_regs.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"

int title_screen(alt_up_pixel_buffer_dma_dev*,alt_up_char_buffer_dev *, int, alt_up_ps2_dev *, KB_CODE_TYPE,alt_u8, char );


#endif /* TITLE_SCREEN_H_ */
