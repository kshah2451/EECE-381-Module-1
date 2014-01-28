#ifndef _CURSOR_H_
#define _CURSOR_H_

#include "game_structs.h"
#include "graphics.h"
#include "title_screen.h"

#define PS2_NAME "/dev/ps2"
#define PS2_TYPE "altera_up_avalon_ps2"
#define PS2_BASE 0x00004030
#define PS2_SPAN 8
#define PS2_IRQ 0
#define PS2_HDL_PARAMETERS ""
#define ALT_MODULE_CLASS_ps2 altera_up_avalon_ps2

void move_cursor();

#endif