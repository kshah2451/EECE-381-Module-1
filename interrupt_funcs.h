/*
 * interrupt_funcs.h
 *
 *  Created on: 2014-01-30
 *      Author: User
 */

#ifndef INTERRUPT_FUNCS_H_
#define INTERRUPT_FUNCS_H_
#include <stdio.h>
#include <stdlib.h>
#include "game_structs.h"
#include <sys/alt_irq.h>
#include <altera_avalon_timer_regs.h>


//Interrupt function
void timerroutine(void* context, alt_u32 id);




//Functions for enemy advancement
void goEnemies(dataPtr data);

//Function that determines if it's time for a new enemy to be made
int isNewEnemy(void);

//Functions for enemies
enePtr createEnemy(enePtr prevEne, int row);

//Function to detect shark attacks
void sharkAttack(enePtr ene, towPtr tow, dataPtr data);

//More enemy functions
void moveEnemy(enePtr ene);







//Function for bullet advancement
void goBullets(towPtr tow, dataPtr data);

//Checks if it's time for a new bullet
int isNewBullet(towPtr tow);

//Functions for bullets
bulPtr createBullet(towPtr ownerTow, bulPtr prevBul);
void moveBullet(bulPtr bul);
void killBullet(bulPtr bul, towPtr ownerTow);
void killEnemy(enePtr ene, dataPtr data, int i);




//Function to detect collision, will call the kill functions
void detectCollision(dataPtr data, towPtr tow, bulPtr bul);




#endif /* INTERRUPT_FUNCS_H_ */
