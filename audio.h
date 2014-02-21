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
//File size is bytes and was determined by reading the properties in Windows

extern unsigned int tracker_l; //keeps track of position in audio file for the left buffer, defined in main
extern unsigned int tracker_r; //keeps track of position in audio file for the left buffer, define in main

unsigned int* load_audio(int); //reads wav file from SD Card, concatenates into playable samples and dynamically allocates memory
void play_loop(unsigned int*,alt_up_audio_dev*,int);//plays an arbitrary number of samples from a file, needs to placed in a loop to create background music
void play_once(unsigned int*,alt_up_audio_dev*,int);//plays the entire wav file, used for sound effects and short sound clips

#endif /* AUDIO_H_ */
