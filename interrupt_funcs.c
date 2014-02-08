#include "interrupt_funcs.h"
#include "graphics.h"
#include "background_graphics.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"

extern alt_up_pixel_buffer_dma_dev* pixel_buffer;
extern int gameOverFlag;
extern int victoryFlag;


//Interrupt function
void timerroutine(void* context, alt_u32 id){

	dataPtr data = (dataPtr)context;

	int i;


	//Advance/create enemies
	goEnemies(data);
	//	draw_grids(pixel_buffer);
	//	draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);



	//Advance/create bullets by tower
	for(i = 0; i < NUMTOW; i++){


		//if the tower exists
		if(data->towers[i]->isAlive){

			//then advance/create its bullets
			goBullets(data->towers[i], data);
			//draw_grids(pixel_buffer);
			//draw_cursor(cur.pos, CURSOR_COLOUR, pixel_buffer);


		}



	}


	//Clear interrupt
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);
}




//Function for enemy advancement
void goEnemies(dataPtr data){

	int i;
	towPtr tow = NULL;

	//row by row
	for(i = 0; i < NUMROW; i++){

		//find the first tower in a row
		int firstTow = (NUMTOW/NUMROW)*i;




		//if there's no enemies in that row, try and make one
		if(data->eneHead[i] == NULL){
			if(isNewEnemy()){
				data->eneHead[i] = createEnemy(NULL, i);
				moveEnemy(data->eneHead[i]);
			}
		}


		//point to the first enemy in the row
		enePtr ene = data->eneHead[i];



		//check if we even need to do this check
		if (ene != NULL){
			//point to the first living tower in the row, or to NULL if no towers alive
			tow = (data->towers[firstTow]);
			while(tow != NULL && !tow->isAlive){

				if(firstTow < ((NUMTOW/NUMROW)*(i + 1))){
					firstTow++;
					tow = (data->towers[firstTow]);
				}
				else tow = NULL;

			}
		}

		//Go through enemies until we hit the end of the list
		while(ene != NULL){
			//try to attack then move
			sharkAttack(ene, tow, data);
			moveEnemy(ene);

			//if at the end of the enemies, try and make a new one
			if(ene->next == NULL){
				if(isNewEnemy()){
					ene = createEnemy(ene, i);
					moveEnemy(ene);
				}
			}

			//move on to the next enemy
			ene = ene->next;
		}
	}



}


//Checks if we should make a new enemy
int isNewEnemy(void){

	//
	//
	//INCOMPLETE, THIS IS JUST FOR TEST
	//
	//

	int q = rand() % 100;

	if(q == 1)return 1;
	else return 0;

}

//Creates a new enemy
enePtr createEnemy(enePtr prevEne, int row){


	int randType = rand() % NUMENETYPES;

	//Malloc some space for the enemy
	enePtr ene = malloc(sizeof(Enemy));

	//Enemies type is random, and determines their stats
	ene->type = randType;

	switch(randType){

	//Normal Shark
	case 0:
		ene -> damage = 3;
		ene -> health = 15;
		ene -> speed = 5;
		ene -> toAttack = 5;
		ene -> baseAttack = 5;
		ene -> toMove = 7;
		ene -> baseMove = 7;
		ene -> moveBlocked = 0;
		ene -> status = 0;
		ene -> statusCountdown = 0;
		ene -> colour = 0x7bef;
		break;

	//Fast shark
	case 1:
		ene -> damage = 4;
		ene -> health = 9;
		ene -> speed = 6;
		ene -> toAttack = 3;
		ene -> baseAttack = 3;
		ene -> toMove = 4;
		ene -> baseMove = 4;
		ene -> moveBlocked = 0;
		ene -> status = 0;
		ene -> statusCountdown = 0;
		ene -> colour = 0xffff;
		break;

	//Armored shark
	case 2:
		ene -> damage = 2;
		ene -> health = 30;
		ene -> speed = 3;
		ene -> toAttack = 5;
		ene -> baseAttack = 5;
		ene -> toMove = 7;
		ene -> baseMove = 7;
		ene -> moveBlocked = 0;
		ene -> status = 0;
		ene -> statusCountdown = 0;
		ene -> colour = 0x0000;
		break;


	//Kamikaze shark  !!!!SPECIAL SHARK!!!!
	case 3:
		ene -> damage = 20;
		ene -> health = 15;
		ene -> speed = 6;
		ene -> toAttack = 0;
		ene -> baseAttack = 0;
		ene -> toMove = 7;
		ene -> baseMove = 7;
		ene -> moveBlocked = 0;
		ene -> status = 0;
		ene -> statusCountdown = 0;
		ene -> colour = 0x00ff;
		break;


	//Mini-Boss shark !!!!SPECIAL SPAWNRATE!!!!
	case 4:
		ene -> damage = 10;
		ene -> health = 40;
		ene -> speed = 3;
		ene -> toAttack = 5;
		ene -> baseAttack = 5;
		ene -> toMove = 7;
		ene -> baseMove = 7;
		ene -> moveBlocked = 0;
		ene -> status = 0;
		ene -> statusCountdown = 0;
		ene -> colour = 0x0ff0;
		break;


	//FINARU BOSSU SHAKKU  !!!!SPECIAL EVERYTHING, MAY REMOVE FROM HERE!!!!
	case 5:
		ene -> damage = 50;
		ene -> health = 60;//300;
		ene -> speed = 3;
		ene -> toAttack = 5;
		ene -> baseAttack = 5;
		ene -> toMove = 10;
		ene -> baseMove = 10;
		ene -> moveBlocked = 0;
		ene -> status = 0;
		ene -> statusCountdown = 0;
		ene -> colour = 0x9955;
		break;

	}

	//row determines their y-pos
	switch(row){

	case 0:
		ene -> body_pos[0] = 320;
		ene -> body_pos[1] = 45;
		break;

	case 1:
		ene -> body_pos[0] = 320;
		ene -> body_pos[1] = 85;
		break;

	case 2:
		ene -> body_pos[0] = 320;
		ene -> body_pos[1] = 125;
		break;

	case 3:
		ene -> body_pos[0] = 320;
		ene -> body_pos[1] = 165;
		break;

	}

	//since this is the newest enemy, next is null, and then point to previous enemy (or NULL) and have it point back if there is one
	ene -> next = NULL;
	ene -> prev = prevEne;
	if(prevEne != NULL) prevEne -> next = ene;

	return ene;

}

//Function to detect shark attacks
void sharkAttack(enePtr ene, towPtr tow, dataPtr data){



	if(tow->isAlive == 0 || tow == NULL){
		ene->moveBlocked = 0;
		ene->toAttack = ene->baseAttack;
		return;
	}

	if((ene->body_pos[0] - 24) <= (tow->body_pos[2]) ){

		if(ene->type == 3){
			tow->health -= ene->damage;
			killEnemy(ene, data, tow->lane);

			if(tow->health <= 0){

				//
				//
				//REMOV BABY HERE REMOVE BELOW ISALIVE
				//
				//
				tow->isAlive = 0;
			}
			return;
		}

		ene->moveBlocked = 1;

		if(ene->toAttack <= 0){
			ene->toAttack = ene->baseAttack;
			tow->health -= ene->damage;

			if(tow->health <= 0){

				//
				//
				//REMOV BABY HERE REMOVE BELOW ISALIVE
				//
				//


				tow->isAlive = 0;
				ene->moveBlocked = 0;
			}
		}
		else ene->toAttack--;
	}

}

//Function to increment enemy positions
void moveEnemy(enePtr ene){

	if (ene->moveBlocked == 0){
		if(ene->toMove <= 0){

			if((ene->body_pos[0] - 24) <= 16){


				//
				//
				//GAME OVER GOES HERE, REMEMBER TO FREE ALL MEM EITHER HERE OR OUTSIDE
				//
				//

				gameOverFlag = 1;

				ene-> moveBlocked = 1;

				return;
			}
			ene->toMove = ene->baseMove;

			draw_background_sharkfin(pixel_buffer, ene->body_pos[0], ene->body_pos[1]);

			ene->body_pos[0] -= ene->speed;
			draw_sharkfin(pixel_buffer, ene->body_pos[0], ene->body_pos[1], ene -> colour);



		}
		else ene->toMove--;
	}


}





//Function for bullet advancement/creation
void goBullets(towPtr tow, dataPtr data){

	int bulFlag = 0;

	//if there's no bullet for that tower, try and make one
	if(tow->bulHead == NULL  && tow->bulletType != 2 && tow->bulletType != 4 && tow->bulletType != 5){
		if(isNewBullet(tow)){
			tow->bulHead = createBullet(tow, NULL);
			moveBullet(tow->bulHead);
			detectCollision(data, tow, tow->bulHead);
		}
	}

	//point to the first bullet
	bulPtr bul = tow->bulHead;



	//Go through bullets until we hit the end of the list
	while(bul != NULL){

		//if at the end of the bullets, try and make a new one
		if(bul->next == NULL)
			if(isNewBullet(tow) && bulFlag == 0){
				bul = createBullet(tow, bul);
			}
		bulFlag = 1;
		//move then detect collisions
		moveBullet(bul);
		detectCollision(data, tow, bul);
		if(bul->body_pos[0] >= 320)
			killBullet(bul, tow);


		//move on to the next bullet
		bul = bul->next;
	}


}

//Checks if it's time for a new bullet
int isNewBullet(towPtr tow){



	if(tow->toAttack <= 0){
		tow->toAttack = tow->baseAttack;
		return 1;
	}
	else{
		tow->toAttack--;
		return 0;
	}
	return 0;
}


bulPtr createBullet(towPtr ownerTow, bulPtr prevBul){

	//Malloc some space for the bullet
	bulPtr bul = malloc(sizeof(Bullet));

	//Bullet type is based on tower, and determines their stats
	bul->type = ownerTow->bulletType;
	bul -> body_pos[0] = ownerTow->body_pos[2]+1;
	bul -> body_pos[1] = ownerTow->body_pos[1]-2;

	switch(bul->type){

	//Normal Tower
	case 1:
		bul -> damage = 3;
		bul -> speed = 5;
		bul -> toMove = 1;
		bul -> baseMove = 1;
		bul -> colour = 0xFFFF;
		break;

	//Resource Tower  !!!!SPECIAL CASE, SHOULDNT MAKE BULLETS AT THIS BUL TYPE!!!!
	case 2:
		bul -> damage = 0;
		bul -> speed = 0;
		bul -> toMove = 0;
		bul -> baseMove = 0;
		bul -> colour = 0;
		break;

	//Rapid Fire
	case 3:
		bul -> damage = 1;
		bul -> speed = 8;
		bul -> toMove = 1;
		bul -> baseMove = 1;
		bul -> colour = 0x0F00;
		break;

	//Mine 	!!!!SPECIAL CASE, SHOULDN'T MAKE BULLETS AT THIS TYPE!!!!
	case 4:
		bul -> damage = 0;
		bul -> speed = 0;
		bul -> toMove = 0;
		bul -> baseMove = 0;
		bul -> colour = 0;
		break;

	//Defensive Tower 	!!!!SPECIAL CASE, SHOULDN'T MAKE BULLETS AT THIS TYPE!!!!
	case 5:
		bul -> damage = 0;
		bul -> speed = 0;
		bul -> toMove = 0;
		bul -> baseMove = 0;
		bul -> colour = 0;
		break;

	//Poison Tower    !!!!SPECIAL TOWER, POISON EFFECT!!!!
	case 6:
		bul -> damage = 2;
		bul -> speed = 5;
		bul -> toMove = 1;
		bul -> baseMove = 1;
		bul -> colour = 0xF00F;
		break;

	//Ice Tower    !!!!SPECIAL TOWER, SLOW EFFECT!!!!
	case 7:
		bul -> damage = 2;
		bul -> speed = 5;
		bul -> toMove = 1;
		bul -> baseMove = 1;
		bul -> colour = 0x000F;
		break;

	//Rocket Tower
	case 8:
		bul -> damage = 8;
		bul -> speed = 7;
		bul -> toMove = 1;
		bul -> baseMove = 1;
		bul -> colour = 0x0000;
		break;

	}

	//since this is the newest bullet, next is null, and then point to previous bullet (or NULL) and have it point back if there is one
	bul -> next = NULL;
	bul -> prev = prevBul;
	if(prevBul != NULL) prevBul -> next = bul;

	return bul;
}


void moveBullet(bulPtr bul){
	if(bul->toMove <= 0){

		draw_background_bullet(pixel_buffer, bul->body_pos[0], bul->body_pos[1]);


		bul->body_pos[0] += bul->speed;
		bul->toMove = bul->baseMove;

		//
		//
		//DRAW IT HERE
		//

		draw_bullet(pixel_buffer, bul->body_pos[0], bul->body_pos[1], bul -> colour);


		//

	}
	else bul->toMove--;
}


void killBullet(bulPtr bul, towPtr ownerTow){
	//DRAW OVER THE BULLET WITH BACKGROUND
	draw_background_bullet(pixel_buffer, bul->body_pos[0], bul->body_pos[1]);

	if(bul->prev != NULL){
		(bul->prev)->next = bul->next;
	}
	else ownerTow->bulHead = bul->next;

	if(bul->next != NULL){
		(bul->next)->prev = bul->prev;
	}

	bul->next = NULL;
	bul->prev = NULL;
	free(bul);
}

void killEnemy(enePtr ene, dataPtr data, int i){
	//
	//
	//DRAW OVER THE SHARK WITH BACKGROUND
	//
	//
	draw_background_sharkfin(pixel_buffer, ene->body_pos[0], ene->body_pos[1]);

	if(ene->prev != NULL){
		(ene->prev)->next = ene->next;
	}
	else data->eneHead[i] = ene->next;

	if(ene->next != NULL){
		(ene->next)->prev = ene->prev;
	}

	ene->next = NULL;
	ene->prev = NULL;
	free(ene);

	victoryFlag++;

}


//Function to detect collision, will call the kill functions
void detectCollision(dataPtr data, towPtr tow, bulPtr bul){



	enePtr ene = data->eneHead[(tow->lane)];


	while(ene != NULL){
		if((ene->body_pos[0] - 24) <= (bul->body_pos[0]) ){

			ene->health -= bul->damage;
			killBullet(bul,tow);

			if(ene->health <= 0) killEnemy(ene, data, (tow->lane));
			return;

		}
		ene = ene->next;


	}


}



