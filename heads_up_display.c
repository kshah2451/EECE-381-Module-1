#include "heads_up_display.h"

void tower_indicator(int tower_type, alt_up_pixel_buffer_dma_dev* pixel_buffer){
	//Orange is the colouring hi-lighting an unselected tower, Yellow is the colour for a selected tower
	switch(tower_type){//Highlights a tower yellow depending on the type passed in as a parameter
	//Changes hi-lighting back to orange for unselected towers
	case 0: alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer,0,119,12,134,RED,0);//highlights tower 1
			alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer,0,149,12,164,ORANGE,0);
			alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer,0,179,12,194,ORANGE,0);
			break;
	case 1: alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer,0,149,12,164,RED,0);//highlights tower 2
			alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer,0,179,12,194,ORANGE,0);
			alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer,0,119,12,134,ORANGE,0);
			break;
	case 2: alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer,0,179,12,194,RED,0);//highlights tower 3
			alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer,0,119,12,134,ORANGE,0);
			alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer,0,149,12,164,ORANGE,0);
			break;
	}
}
void heads_up_display_static(void){
	alt_up_char_buffer_dev *char_buffer_score;
	alt_up_pixel_buffer_dma_dev* pixel_buffer;

	char_buffer_score = alt_up_char_buffer_open_dev("/dev/char_drawer");
	alt_up_char_buffer_init(char_buffer_score); //initializes character buffer
	alt_up_char_buffer_clear(char_buffer_score); //clears the character buffer of an previous characters
	alt_up_char_buffer_string(char_buffer_score,"Score:", 5, 50); //updates score
	alt_up_char_buffer_string(char_buffer_score,"Milk:", 5, 52); //updates resources
	alt_up_char_buffer_string(char_buffer_score,"Level:", 5, 54); //updates level
	alt_up_char_buffer_string(char_buffer_score,"Time:", 5, 56); //updates time

	pixel_buffer = alt_up_pixel_buffer_dma_open_dev("/dev/pixel_buffer_dma");

	alt_up_pixel_buffer_dma_draw_box(pixel_buffer,1,120,11,130,BLACK,0);//draws black baby's body
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer,1,130,11,133,WHITE,0);//draws diaper

	alt_up_pixel_buffer_dma_draw_box(pixel_buffer,1,150,11,160,BEIGE,0);//draws beige baby's body
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer,1,160,11,163,WHITE,0);//draws diaper

	alt_up_pixel_buffer_dma_draw_box(pixel_buffer,1,180,11,190,YELLOW,0);//draws yellow baby's body
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer,1,190,11,193,WHITE,0);//draws diaper

	//draws rectangle around indicator of tower choice
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer,0,119,12,134,ORANGE,0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer,0,149,12,164,ORANGE,0);
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer,0,179,12,194,ORANGE,0);
}

void heads_up_display_dynamic(int variable_type,int variable,alt_up_char_buffer_dev *char_buffer_time,char* int_buffer){

	switch(variable_type){

	case 0: //Change score
		alt_up_char_buffer_string(char_buffer_time,int_buffer, 12, 50);
	case 1: //Change resources
		alt_up_char_buffer_string(char_buffer_time,int_buffer, 11, 52);
	case 2: //Change level
		alt_up_char_buffer_string(char_buffer_time,int_buffer, 12, 54);
	case 3: //Change time
		alt_up_char_buffer_string(char_buffer_time,int_buffer, 11, 56);

	}

}

