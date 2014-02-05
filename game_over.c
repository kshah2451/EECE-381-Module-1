#include "game_over.h"

void display_score(int score){


}

void gameover(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev * char_buffer){
	int color_inc = 0x0100;
	int x0_pos = 0;
	int x1_pos = 320;
	int change = 4;
	int y_pos;

	// Draws sky
	for(y_pos = 0; y_pos < 45; y_pos++) {
		alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, x0_pos, x1_pos, y_pos, BLACK + color_inc, 0);
		if(y_pos % 3 == 0) color_inc++;
	}

	x0_pos = 155;
	x1_pos = 165;
	// Draws sun
	for(y_pos = 37; y_pos < 45; y_pos++) {
		alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, x0_pos, x1_pos, y_pos, WHITE, 0);
		if(y_pos == 37 || y_pos == 39) change = 4;
		else if(y_pos == 38) change = 3;
		else change = 1;
		x0_pos -= change; x1_pos += change;
	}

	int i;
	// Draws planks
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 0, 45, 14, 240, 0x79E5, 0);
	for(i = 45; i < 240; i+=4 ) {
		alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 0, 14, i, BLACK, 0);
	}

	// Draws ocean
	for(i = 45; i < 240; i++) {
		alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 14, 320, i, RED + color_inc, 0);
		if(i % 8 == 0) color_inc+=0x1000;
	}
	/**Shark Image**/
	//Dorsal Fin
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 198, 66, 202, 68, 0xCEFD, 0); //0xFFFA
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 193, 68, 207, 73, 0xCEFD, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 190, 73, 210, 80, 0xCEFD, 0);

	//Body
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 175, 80, 240, 95, 0xCEFD, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 175, 94, 240, 105, 0xFFFF, 0);
	//alt_up_pixel_buffer_dma_draw(pixel_buffer, 0xC000, 160, 120);

	//Head
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 160, 84, 176, 99, 0xCEFD, 0);


	//Pectoral Fin
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 180, 104, 188, 109, 0xCEFD, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 184, 109, 190, 114, 0xCEFD, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 188, 114, 192, 115, 0xCEFD, 0);

	// Tail
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 240, 86, 250, 97, 0xCEFD, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 250, 88, 255, 95, 0xCEFD, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 255, 80, 265, 90, 0xCEFD, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 255, 95, 265, 105, 0xCEFD, 0);
	/****/

	alt_up_char_buffer_clear(char_buffer);
	alt_up_char_buffer_string(char_buffer, "ALL YOUR BASE ARE BELONG TO US", 32, 32);
	//alt_up_char_buffer_string(char_buffer, "PRESS A TO RETURN TO MAIN MENU", 32, 42);

}
