/*
 * tower_select.h
 *
 *  Created on: 2014-01-31
 *      Author: Cyril
 */

#ifndef TOWER_SELECT_H_
#define TOWER_SELECT_H_


#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"
#include "game_structs.h"
#include "altera_up_ps2_keyboard.h"
#include "altera_up_avalon_ps2.h"
#include "altera_up_avalon_ps2_regs.h"


//


void tower_selection(alt_up_ps2_dev* , KB_CODE_TYPE , alt_u8 , char, int* );
void remove_baby(Tower* baby, int, alt_up_pixel_buffer_dma_dev*);

#endif /* TOWER_SELECT_H_ */
