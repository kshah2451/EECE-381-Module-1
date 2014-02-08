#ifndef MINIGAME_H_
#define MINIGAME_H_

#include "graphics.h"
#include "game_structs.h"
#include "keyboard_codes.h"

#define BOAT_X_INC 40

void initialize_boat(alt_up_pixel_buffer_dma_dev* pixel_buffer, Boat * boat, int x_pos, int y_pos, int height, int width);

void move_boat(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_u8 data, Boat * boat);




#endif
