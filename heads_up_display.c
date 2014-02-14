#include "heads_up_display.h"
#include <stdlib.h>

extern int resources;
extern alt_up_pixel_buffer_dma_dev* pixel_buffer;
extern alt_up_char_buffer_dev* char_buffer;



void tower_indicator(int tower_type, alt_up_pixel_buffer_dma_dev* pixel_buffer){
	//Orange is the colouring hi-lighting an unselected tower, Yellow is the colour for a selected tower
	int start = 23;
	int end = 47;
	alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer,start + 28*(tower_type - 1),214,end + 28*(tower_type - 1),238,ORANGE,0);//highlights tower 2
}

void heads_up_display_static(alt_up_pixel_buffer_dma_dev* pixel_buffer, alt_up_char_buffer_dev* char_buffer){
	alt_up_pixel_buffer_dma_draw_box(pixel_buffer, 21, 214, 320, 240, BLACK, 0);
	clear_all_selection(pixel_buffer);


	alt_up_char_buffer_string(char_buffer, "1", 6, 54);
	alt_up_char_buffer_string(char_buffer, "2", 13, 54);
	alt_up_char_buffer_string(char_buffer, "3", 20, 54);
	alt_up_char_buffer_string(char_buffer, "4", 27, 54);
	alt_up_char_buffer_string(char_buffer, "5", 34, 54);
	alt_up_char_buffer_string(char_buffer, "6", 41, 54);
	alt_up_char_buffer_string(char_buffer, "7", 48, 54);
	alt_up_char_buffer_string(char_buffer, "8", 55, 54);

	alt_up_char_buffer_string(char_buffer, "Cst:5", 6, 58);
	alt_up_char_buffer_string(char_buffer, "Cst:7", 13, 58);
	alt_up_char_buffer_string(char_buffer, "Cst:10", 20, 58);
	alt_up_char_buffer_string(char_buffer, "Cst:10", 27, 58);
	alt_up_char_buffer_string(char_buffer, "Cst:7", 34, 58);
	alt_up_char_buffer_string(char_buffer, "Cst:13", 41, 58);
	alt_up_char_buffer_string(char_buffer, "Cst:13", 48, 58);
	alt_up_char_buffer_string(char_buffer, "Cst:15", 55, 58);



	alt_up_char_buffer_string(char_buffer, "Cow", 6, 56);
	alt_up_char_buffer_string(char_buffer, "Normal", 13, 56);
	alt_up_char_buffer_string(char_buffer, "Rapid", 20, 56);
	alt_up_char_buffer_string(char_buffer, "Wall", 27, 56);
	alt_up_char_buffer_string(char_buffer, "Mine", 34, 56);
	alt_up_char_buffer_string(char_buffer, "Freeze", 41, 56);
	alt_up_char_buffer_string(char_buffer, "Poison", 48, 56);
	alt_up_char_buffer_string(char_buffer, "Rocket", 55, 56);





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

void clear_all_selection(alt_up_pixel_buffer_dma_dev* pixel_buffer) {
	int i;
	int start = 23;
	int end = 47;
	int box_colour= 0;
	for(i = 0; i < 8; i++) {
		switch (i){
		case 0:
			box_colour = 0x0000;
			break;
		case 1:
			box_colour = 0xD2CB;
			break;
		case 2:
			box_colour = ORANGE;
			break;
		case 3:
			box_colour = 0xBDF7;
			break;
		case 4:
			box_colour = 0x89E0;
			break;
		case 5:
			box_colour = 0x0E;
			break;
		case 6:
			box_colour = 0xF00A;
			break;

		case 7:
			box_colour = 0xBDF7;
			break;

		}


		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, start, 214, end , 238, box_colour, 0);
		alt_up_pixel_buffer_dma_draw_rectangle(pixel_buffer, start, 214, end , 238, RED, 0);

		start += 28;
		end += 28;
	}
}


void display_resources(void){
	char resources_string[5];


	if(resources < 10){
		sprintf(resources_string, "0%d", resources);
	}
	else{
		sprintf(resources_string, "%d", resources);
	}

	alt_up_pixel_buffer_dma_draw_box(pixel_buffer,255, 16, 305, 25, 0x0000, 0);
	alt_up_char_buffer_string(char_buffer,"Resources:", 64, 5);
	alt_up_char_buffer_string(char_buffer,resources_string, 74, 5);

}


void display_health(int health){
	char health_string[5];


	if(health < 10){
		sprintf(health_string, "0%d", health);
	}
	else{
		sprintf(health_string, "%d", health);
	}
	alt_up_char_buffer_string(char_buffer,"Tower Health: ",  62, 54);
	alt_up_char_buffer_string(char_buffer,health_string, 64, 56);


}


