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
void sharkAttack(enePtr ene, towPtr tow);

//More enemy functions
void moveEnemy(enePtr ene);
void killEnemy(void);





//Function for bullet advancement
void goBullets(Tower tow);

//Functions for bullets
bulPtr createBullet(Tower ownerTow, bulPtr prevBul);
void moveBullet(bulPtr bul);
void killBullet(void);




//Function to detect collision, will call the kill functions
void detectCollision(enePtr ene, bulPtr bul);




#endif /* INTERRUPT_FUNCS_H_ */
