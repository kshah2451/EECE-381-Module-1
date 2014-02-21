/*
 * cursor.h
 *
 *  Created on: 2014-01-31
 *      Author: Cyril
 */

#ifndef CURSOR_H_
#define CURSOR_H_
/*
#define PS2_NAME "/dev/ps2"
#define PS2_TYPE "altera_up_avalon_ps2"
//#define PS2_BASE 0x00004030
#define PS2_SPAN 8
#define PS2_IRQ 0
#define PS2_HDL_PARAMETERS ""
#define ALT_MODULE_CLASS_ps2 altera_up_avalon_ps2
*/
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"
#include "game_structs.h"
#include "altera_up_ps2_keyboard.h"
#include "altera_up_avalon_ps2.h"
#include "altera_up_avalon_ps2_regs.h"

// moves the cursor depending on what directional key is pressed, updates grid position of cursor
int move_cursor(int, alt_up_ps2_dev *, KB_CODE_TYPE, alt_u8, char , alt_up_pixel_buffer_dma_dev* );

//
#endif /* CURSOR_H_ */
