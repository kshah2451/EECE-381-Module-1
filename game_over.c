#include "game_over.h"

void display_score(int score){


}


void victory(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev * char_buffer){
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
		alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 14, 320, i, RED/* + color_inc*/, 0);
		if(i % 8 == 0) color_inc+=0x1000;
	}
	//Baby
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 100, 80, 115, 110, 0xFE99, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 95, 90, 120, 110, 0xFE99, 0);

	//Eyes
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 104, 82, 106, 84, 0x0000, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 110, 82, 112, 84, 0x0000, 0);


	//Arms
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 90, 92, 100, 100, 0xFE99, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 115, 92, 125, 100, 0xFE99, 0);

	//Gun
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 122, 92, 124, 98, 0xCEFD, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 125, 92, 132, 94, 0xCEFD, 0);
	// Diapers
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 95, 102, 120, 110, 0xAFFF, 0);

	//Legs
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 90, 106, 100, 114, 0xFE99, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 115, 106, 125, 114, 0xFE99, 0);

	alt_up_char_buffer_clear(char_buffer);
	alt_up_char_buffer_string(char_buffer, "YOU WIN!", 34, 30);
	alt_up_char_buffer_string(char_buffer, "SHARK FIN SOUP FOR EVERYONE!", 34, 32);
	//alt_up_char_buffer_string(char_buffer, "PRESS A TO RETURN TO MAIN MENU", 32, 42);

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
		alt_up_pixel_buffer_dma_draw_hline(pixel_buffer, 14, 320, i, RED/* + color_inc*/, 0);
		if(i % 8 == 0) color_inc+=0x1000;
	}
	/**Shark Image**/
	//Dorsal Fin
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 188, 66, 192, 68, 0xCEFD, 0); //0xFFFA
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 183, 68, 197, 73, 0xCEFD, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 180, 73, 200, 80, 0xCEFD, 0);

	//Body
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 165, 80, 230, 95, 0xCEFD, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 165, 94, 230, 105, 0xFFFF, 0);
	//alt_up_pixel_buffer_dma_draw(pixel_buffer, 0xC000, 160, 120);

	//Head
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 150, 84, 166, 99, 0xCEFD, 0);


	//Pectoral Fin
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 170, 104, 178, 109, 0xCEFD, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 174, 109, 180, 114, 0xCEFD, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 178, 114, 182, 115, 0xCEFD, 0);

	// Tail
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 230, 86, 240, 97, 0xCEFD, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 240, 88, 245, 95, 0xCEFD, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 245, 80, 255, 90, 0xCEFD, 0);
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 245, 95, 255, 105, 0xCEFD, 0);
	/****/

	alt_up_char_buffer_clear(char_buffer);
	alt_up_char_buffer_string(char_buffer, "GAME OVER (LOSER)!", 22, 8);
	alt_up_char_buffer_string(char_buffer, "ALL YOUR BASE ARE BELONG TO US", 18, 34);
	//alt_up_char_buffer_string(char_buffer, "PRESS A TO RETURN TO MAIN MENU", 32, 42);

}
