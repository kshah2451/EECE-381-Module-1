#ifndef AUDIO_H_
#define AUDIO_H_

#include <stdio.h>
#include <assert.h>
#include <system.h>
#include <stdlib.h>
#include <altera_up_avalon_audio.h>
#include <altera_up_sd_card_avalon_interface.h>

#define FILESIZEOF_TITLE 803244
#define FILESIZEOF_GAMEOVER 329396
#define FILESIZEOF_VICTORY 277804
#define FILESIZEOF_FIRST 706028
#define FILESIZEOF_SECOND 640044
#define FILESIZEOF_THIRD 705324
#define FILESIZEOF_BACKGROUND 945298
//unsigned int* load_audio(unsigned char*,alt_up_audio_dev*,int);
unsigned int* load_audio(int);

extern unsigned int tracker_l;
extern unsigned int tracker_r;
void play_loop(unsigned int*,alt_up_audio_dev*,int);
void play_once(unsigned int*,alt_up_audio_dev*,int);

#endif /* AUDIO_H_ */
