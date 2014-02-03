#include "interrupt_funcs.h"



//Interrupt function
void timerroutine(void* context, alt_u32 id){

	dataPtr data = (dataPtr)context;

	int i;



	//Advance/create enemies
	goEnemies(data);

	//DRAW ENEMIES HERE, OR IN GOENEMIES

//COMMENTED OUT FOR KEVAL
/*
	//Advance/create bullets by tower
	for(i = 0; i < NUMTOW; i++){

		//if the tower exists
		if(data->towers[i].isAlive){

			//then advance/create its bullets
			goBullets(data->towers[i]);

			//DRAW BULLETS HERE OR IN GOBULLETS
		}

	}

*/
	//Clear interrupt
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0);
}




//Function for enemy advancement
void goEnemies(dataPtr data){

	int i;

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
			towPtr tow = &(data->towers[firstTow]);
			while(!tow->isAlive || tow != NULL){

				if(firstTow < ((NUMTOW/NUMROW)*(i + 1))){
					firstTow++;
					tow = &(data->towers[firstTow]);
				}
				else tow = NULL;

			}
		}



		//Go through enemies until we hit the end of the list
		while(ene != NULL){
			//try to attack then move


			//COMMENTED OUT FOR KEVAL
			//sharkAttack(ene, tow);


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
	//INCOMPLETE, THIS IS JUST FOR TEST
	int q = rand() % 100;

	if(q == 1)return 1;
	else return 0;

}

//Creates a new enemy
enePtr createEnemy(enePtr prevEne, int row){


	int randType = rand() % NUMENETYPES;

	//Malloc some space for the memblock
	enePtr ene = malloc(sizeof(Enemy));

	//Enemies type is random, and determines their stats
    ene->type = randType;

    switch(randType){

        case 1:
        	ene -> damage = 1;
        	ene -> health = 1;
        	ene -> speed = 1;
        	ene -> toAttack = 1;
        	ene -> baseAttack = 1;
        	ene -> toMove = 100;
        	ene -> moveBlocked = 0;
        	ene -> colour = 0x7bef;
        break;

        case 2:
        	ene -> damage = 1;
        	ene -> health = 1;
        	ene -> speed = 1;
        	ene -> toAttack = 1;
        	ene -> baseAttack = 1;
        	ene -> toMove = 200;
        	ene -> moveBlocked = 0;
        	ene -> colour = 0xffff;
        break;

    }

    //row determines their y-pos
    switch(row){

    	case 1:
    		ene -> body_pos[0] = 320;
    		ene -> body_pos[1] = 45;
        break;

        case 2:
        	ene -> body_pos[0] = 320;
        	ene -> body_pos[1] = 85;
        break;

    }

    //since this is the newest enemy, next is null, and then point to previous enemy (or NULL) and have it point back if there is one
	ene -> next = NULL;
	ene -> prev = prevEne;
	if(prevEne != NULL) prevEne -> next = ene;

	return ene;

}

//Function to detect shark attacks
//void sharkAttack(enePtr ene, towPtr tow);

//Function to increment enemy positions
void moveEnemy(enePtr ene){

	if (ene->moveBlocked == 0){

		//SOMEONE CHANGE THE VALUES AND/OR LOGIC IN HERE/toMove/baseMove/speed TO MAKE ANIMATION GET
		if(ene->toMove <= 0){
			ene->body_pos[0] -= ene->speed;
			ene->toMove = ene->baseMove;
		}
		else ene->toMove--;
	}


}

/*

void killEnemy(void);


//Function for bullet advancement/creation
void goBullets(Tower tow);

//Functions for bullets
bulPtr createBullet(Tower ownerTow, bulPtr prevBul);
void moveBullet(bulPtr bul);
void killBullet(void);



//Function to detect collision, will call the kill functions
void detectCollision(enePtr ene, bulPtr bul);



*/
