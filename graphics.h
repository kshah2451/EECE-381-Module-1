#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"
#include "game_structs.h"

#define MAX_GRIDS 16
#define CURSOR_COLOUR 0x0088
#define SEA_COLOUR 0x0099
#define BG_UPPER_X 0
#define BG_LOWER_X 320
#define BG_UPPER_Y 60
#define BG_LOWER_Y 140

void initialize_baby(int tower.health, int tower.bullet, int tower.fire_rate, int tower.body_pos[], int tower.colour);
void initialize_sharks(int enemy.type, int enemy.damage, int enemy.health, int enemy.speed, int enemy.attack_rate, int enemy.body_pos[], int enemy.colour);
void initialize_cursor(int, int);
void draw_baby(int tower.body_pos[], int tower.colour, alt_up_pixel_buffer_dma_dev* pixel_buffer);
void draw_shark(int enemy.body_pos[],int sharks.colour, alt_up_pixel_buffer_dma_dev* pixel_buffer);
void draw_cursor(int,int, alt_up_pixel_buffer_dma_dev*);

#endif

