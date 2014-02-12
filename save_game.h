#ifndef SAVE_GAME_H_
#define SAVE_GAME_H_

#include <stdio.h>
#include <altera_up_sd_card_avalon_interface.h>
#include <system.h>
#include <stdlib.h>

void save_level(char);
char load_save(void);

#endif /* SAVE_GAME_H_ */
