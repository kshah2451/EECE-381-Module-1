/*
 * game_structs.h
 *
 *  Created on: 2014-01-28
 *      Author: Cyril
 */

#ifndef GAME_STRUCTS_H_
#define GAME_STRUCTS_H_

//#include "title_screen.h"
//#include "graphics.h"
#include <stdlib.h>


#define NUMTOW 14
#define NUMROW 2

//Max number of enemy types per level
#define NUMENETYPES 2





/* Tower/Babies Struct*/
typedef struct Tower
{
	int health;

	//Type of bullet this tower makes
	int bulletType;

	//Countdown to attack
	int toAttack;

	//Value to reset attack countdown
	int baseAttack;


	// Position of Tower's body (assuming tower is just a rectangle)
	//right x-coordinate = position[0], right y-coordinate = pos[1],
	//left x-coordinate = pos[2], left y-coordinate = pos[3]
	int body_pos[4];
	int diaper_pos[4];
	// vga info like the boxes that make up the image and colour
	int colour;

	//if tower is dead or not placed
	//0 for no, 1 for yes
	int isAlive;

	//pointer to the earliest created of this towers bullets
	struct Bullet* bulHead;

}Tower;
typedef Tower* towPtr;


/*Enemy/Sharks struct*/
typedef struct Enemy
{
        int type;
        int damage;
        int health;
        int speed;

        //Countdown to attack
        int toAttack;

        //Value to reset attack countdown
        int baseAttack;

        // Position of top right of fin 0 is x, 1 is y
        int body_pos[2];

        // Countdown until enemy moves
        int toMove;

        //Value to reset move countdown
        int baseMove;

        //If at a tower, don't move
        int moveBlocked;

        // vga info like the boxes that make up the image and colour
        int colour;

        //pointer to the next and previous enemies
        struct Enemy* next;
        struct Enemy* prev;

}Enemy;
typedef Enemy* enePtr;

/*Bullet struct*/
typedef struct Bullet
{
        int damage;
        int type;


        int speed;
        // vga info like colour
        int colour;

        // Position of top left of bullet 0 is x, 1 is y
        int body_pos[2];

        // Countdown until enemy moves
        int toMove;

        //Value to reset move countdown
        int baseMove;

        //pointer to next and previous bullet
        struct Bullet* next;
        struct Bullet* prev;

}Bullet;
typedef Bullet* bulPtr;

/*Game HUD struct*/
typedef struct HUD
{
        int score;
        int milk; // used as resource/currency
        int current_level;
        int available_towers;
        int level_time;


} HUD;

typedef struct gameData {

	//list of towers
	struct Tower* towers[NUMTOW];

	//pointer to first enemy in the row
	struct Enemy* eneHead[NUMROW];



} gameData;
typedef gameData* dataPtr;

/*Management struct*/
typedef struct Management
{
        int game_state; // e.g. 0 = title screen, 1 = some menu, 2 = in game
        int enemy_count;
        int phaseFlag; //subject to removal

} Management;

/*Cursor struct*/
typedef struct Cursor
{
        int pos[4];                // where it is in the grid
        int state;                // on or off
        int colour;

} Cursor;
Cursor cur;
Cursor prev_cur;





#endif /* GAME_STRUCTS_H_ */
