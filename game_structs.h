/*
 * game_structs.h
 *
 *  Created on: 2014-01-28
 *      Author: Cyril
 */

#ifndef GAME_STRUCTS_H_
#define GAME_STRUCTS_H_

#include "title_screen.h"
#include "graphics.h"
#include <stdlib.h>


/* Tower/Babies Struct*/
typedef struct
{
	int health;
	int bullet;
	int fire_rate;
	// Position of Tower's body (assuming tower is just a rectangle)
	//right x-coordinate = position[0], right y-coordinate = pos[1],
	//left x-coordinate = pos[2], left y-coordinate = pos[3]
	int body_pos[4];
	int diaper_pos[4];
	// vga info like the boxes that make up the image and colour
	int colour;


}Tower;



/*Enemy/Sharks struct*/
typedef struct
{
        int type;
        int damage;
        int health;
        int speed;
        int attack_rate;
        // Position of Enemy's body (assuming enemy is just a rectangle)
        //right x-coordinate = position[0], right y-coordinate = pos[1],
        //left x-coordinate = pos[2], left y-coordinate = pos[3]
        int body_pos[4];
        int ID;
        // vga info like the boxes that make up the image and colour
        int colour;

}Enemy;

/*Bullet struct*/
typedef struct
{
        int damage;
        int type;
        // Position of a single bullet
        //right x-coordinate = position[0], right y-coordinate = pos[1],
        //left x-coordinate = pos[2], left y-coordinate = pos[3]
        int pos[4];
        int speed;
        // vga info like colour
        int colour;
}Bullet;

/*Game HUD struct*/
typedef struct
{
        int score;
        int milk; // used as resource/currency
        int current_level;
        int available_towers;
        int level_time;


} HUD;

/*Management struct*/
typedef struct
{
        int game_state; // e.g. 0 = title screen, 1 = some menu, 2 = in game
        int enemy_count;
        int phaseFlag; //subject to removal

} Management;

/*Cursor struct*/
typedef struct
{
        int pos[4];                // where it is in the grid
        int state;                // on or off
        int colour;

} Cursor;
Cursor cur;
Cursor prev_cur;





#endif /* GAME_STRUCTS_H_ */
