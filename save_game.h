#ifndef SAVE_GAME_H_
#define SAVE_GAME_H_

#include <stdio.h>
#include <altera_up_sd_card_avalon_interface.h>
#include <system.h>
#include <stdlib.h>

void save_level(char); //function to write a char to a text file
char load_save(void); //function to read a char from text file, returns a char indicating level, returns 0 if no saves

#endif /* SAVE_GAME_H_ */
