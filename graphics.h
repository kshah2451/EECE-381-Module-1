#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_
#include "altera_up_avalon_video_pixel_buffer_dma.h"
#include "altera_up_avalon_video_character_buffer_with_dma.h"
#include "game_structs.h"


void initialize_baby(int tower.health, int tower.bullet, int tower.fire_rate, int tower.body_pos[], int tower.colour);
void initialize_sharks(int enemy.type, int enemy.damage, int enemy.health, int enemy.speed, int enemy.attack_rate, int enemy.body_pos[], int enemy.colour);
void initialize_cursor(int cursor.body_pos[], int cursor.colour);
void draw_baby(int tower.body_pos[], int tower.colour, alt_up_pixel_buffer_dma_dev* pixel_buffer);
void draw_shark(int enemy.body_pos[],int sharks.colour, alt_up_pixel_buffer_dma_dev* pixel_buffer);
void draw_cursor(int cursor.pos[],int cursor.colour, alt_up_pixel_buffer_dma_dev* pixel_buffer);

#endif

