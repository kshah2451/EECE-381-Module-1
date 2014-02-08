#include "minigame.h"

void initialize_boat(alt_up_pixel_buffer_dma_dev* pixel_buffer, Boat * boat, int x_pos, int y_pos, int height, int width) {
	boat->grid_position = 0;
	boat->boat_height = height;
	boat->boat_width = width;
	boat->x_pos = x_pos;
	boat->y_pos = y_pos;
	draw_boat(pixel_buffer, boat->x_pos, boat->y_pos, boat->boat_height, boat->boat_width);
}

void move_boat(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_u8 data, Boat * boat) {
	int curr_grid_position = boat->grid_position;
	draw_background_boat(pixel_buffer, boat->x_pos, boat->y_pos, boat->boat_height, boat->boat_width);

	switch(data) {
	case D_KEY:
		if(curr_grid_position >= 0 && curr_grid_position < NUMCOLS - 1) {
			curr_grid_position++;
			boat->x_pos += BOAT_X_INC;
		}
		break;
	case A_KEY:
		if(curr_grid_position > 0 && curr_grid_position <= NUMCOLS - 1) {
			curr_grid_position--;
			boat->x_pos -= BOAT_X_INC;
		}
		break;
	}
	boat->grid_position = curr_grid_position;
	draw_boat(pixel_buffer, boat->x_pos, boat->y_pos, boat->boat_height, boat->boat_width);

}
