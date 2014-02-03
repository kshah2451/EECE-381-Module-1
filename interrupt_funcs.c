#include "interrupt_funcs.h"
#include "graphics.h"
#include "altera_up_avalon_video_pixel_buffer_dma.h"

extern alt_up_pixel_buffer_dma_dev* pixel_buffer;
//Interrupt function
void timerroutine(void* context, alt_u32 id){
	printf("THIS SHIT IS WORKING BEFORE DATAPTR\n");

	dataPtr data = (dataPtr)context;

	int i;


	//Advance/create enemies
	goEnemies(data);




	//Advance/create bullets by tower
	for(i = 0; i < NUMTOW; i++){


		//if the tower exists
		if(data->towers[i]->isAlive){

		//then advance/create its bullets
		goBullets(data->towers[i], data);



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
		printf("FIRSTTOWIS%i\n", firstTow);



		//if there's no enemies in that row, try and make one
		if(data->eneHead[i] == NULL){
			if(isNewEnemy()){
				printf("enegetEX\n");
				data->eneHead[i] = createEnemy(NULL, i);
				printf("eneMAKE\n");
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
			sharkAttack(ene, tow);
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

	int q = rand() % 10;

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

        case 1:
        	ene -> damage = 1;
        	ene -> health = 1;
        	ene -> speed = 5;
        	ene -> toAttack = 1;
        	ene -> baseAttack = 1;
        	ene -> toMove = 5;
        	ene -> baseMove = 5;
        	ene -> moveBlocked = 0;
        	ene -> colour = 0x7bef;
        break;

        case 2:
        	ene -> damage = 1;
        	ene -> health = 1;
        	ene -> speed = 8;
        	ene -> toAttack = 1;
        	ene -> baseAttack = 1;
        	ene -> toMove = 3;
        	ene -> baseMove = 3;
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
void sharkAttack(enePtr ene, towPtr tow){

	if(tow->isAlive == 0 || tow == NULL){
		ene->moveBlocked = 0;
		ene->toAttack = ene->baseAttack;
		return;
	}

	if((ene->body_pos[0] - 24) <= (tow->body_pos[3]) ){
		ene->moveBlocked = 1;

		if(ene->toAttack <= 0){
			ene->toAttack = ene->baseAttack;
			tow->health -= ene->damage;

			if(tow->health <= 0){

				//
				//
				//REMOV BABY IMAGE HERE
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
		//
		//
		//SOMEONE CHANGE THE VALUES AND/OR LOGIC IN HERE/toMove/baseMove/speed TO MAKE ANIMATION GET
		//
		//

		if(ene->toMove <= 0){


			draw_background_sharkfin(pixel_buffer, ene->body_pos[0], ene->body_pos[1]);

			ene->body_pos[0] -= ene->speed;
			draw_sharkfin(pixel_buffer, ene->body_pos[0], ene->body_pos[1], ene -> colour);





			if((ene->body_pos[0] - 24) <= 16){


				//
				//
				//GAME OVER GOES HERE
				//
				//


				return;
			}
			ene->toMove = ene->baseMove;
		}
		else ene->toMove--;
	}


}





//Function for bullet advancement/creation
void goBullets(towPtr tow, dataPtr data){

	//if there's no bullet for that tower, try and make one
	if(tow->bulHead == NULL){
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
		//move then detect collisions
		moveBullet(bul);
		detectCollision(data, tow, bul);

		//move on to the next bullet
		bul = bul->next;
	}
}

//Checks if it's time for a new bullet
int isNewBullet(towPtr tow){

	printf("%i\n", tow->toAttack);


	if(tow->toAttack <= 0){
		printf("yes its time\n");
		tow->toAttack = tow->baseAttack;
		return 1;
	}
	else{
		printf("no its not\n");
		tow->toAttack--;
		printf("%i\n", tow->toAttack);
		return 0;
	}
	return 0;
}


bulPtr createBullet(towPtr ownerTow, bulPtr prevBul){
	printf("bullet CREATION\n");
	//Malloc some space for the bullet
	bulPtr bul = malloc(sizeof(Bullet));

	//Bullet type is based on tower, and determines their stats
	bul->type = ownerTow->bulletType;
	bul -> body_pos[0] = ownerTow->body_pos[2]+1;
	bul -> body_pos[1] = ownerTow->body_pos[1]-2;

	switch(bul->type){

		case 1:
			bul -> damage = 1;
			bul -> speed = 1;
			bul -> toMove = 1;
			bul -> baseMove = 1;
			bul -> colour = 0xFFFF;
	    break;

	    case 2:
			bul -> damage = 1;
			bul -> speed = 1;
			bul -> toMove = 1;
			bul -> baseMove = 1;
			bul -> colour = 0x0F00;
	    break;

	}

	//since this is the newest bullet, next is null, and then point to previous bullet (or NULL) and have it point back if there is one
	bul -> next = NULL;
	bul -> prev = prevBul;
	if(prevBul != NULL) prevBul -> next = bul;

	return bul;
}


void moveBullet(bulPtr bul){printf("bullet MOVEMENT\n");
	if(bul->toMove <= 0){
		bul->body_pos[0] += bul->speed;
		bul->toMove = bul->baseMove;

		//
		//
		//DRAW IT HERE
		//

		alt_up_pixel_buffer_dma_draw_box(pixel_buffer, bul->body_pos[0], bul->body_pos[1], bul->body_pos[0]+2, bul->body_pos[1]+2, bul->colour, 0);


		//

	}
	else bul->toMove--;
}


void killBullet(bulPtr bul, towPtr ownerTow){
	//DRAW OVER THE BULLET WITH BACKGROUND

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

}


//Function to detect collision, will call the kill functions
void detectCollision(dataPtr data, towPtr tow, bulPtr bul){


	int i = 0;

	if(tow->body_pos[1] >= 45 && tow->body_pos[1] <= 84){
		i = 0;
	}
	else if(tow->body_pos[1] >= 85 && tow->body_pos[1] <= 124){
		i = 1;
	}
	else if(tow->body_pos[1] >= 125 && tow->body_pos[1] <= 164){
		i = 2;
	}
	else if(tow->body_pos[1] >= 165 && tow->body_pos[1] <= 204){
		i = 3;
	}



	if((data->eneHead[i]->body_pos[0] - 24) <= (bul->body_pos[0]) ){

		data->eneHead[i]->health -= bul->damage;
		killBullet(bul,tow);
		if(data->eneHead[i]->health <= 0) killEnemy(data->eneHead[i], data, i);


	}

}



