#include "audio.h"

//int* load_audio(unsigned char* temp_audio,alt_up_audio_dev* audio,int file_to_load) {
unsigned int* load_audio(int file_to_load) {
	unsigned char* temp_audio;
	unsigned int* audio_buffer;
	short int handle;
	int file_size = 0;
	char *file_name;

	switch(file_to_load){
	case 0: file_size = FILESIZEOF_TITLE;
			file_name = "title.wav";
			break;
	case 1: file_size = FILESIZEOF_VICTORY;
			file_name = "first.wav";
			break;
	case 2: file_size = FILESIZEOF_VICTORY;
			file_name = "second.wav";
			break;
	case 3: file_size = FILESIZEOF_VICTORY;
			file_name = "third.wav";
			break;
	case 9: file_size = FILESIZEOF_GAMEOVER;
			file_name = "gameover.wav";
			break;
	case 99: file_size = FILESIZEOF_VICTORY;
			file_name = "victory.wav";
			break;
	}

	temp_audio = malloc (file_size * sizeof(char));
	audio_buffer = malloc ((file_size/2) * sizeof(int));
	int connected = 0;
	int k,j,m,n;
	alt_up_sd_card_dev *device_reference = NULL;
	device_reference = alt_up_sd_card_open_dev(ALTERA_UP_SD_CARD_AVALON_INTERFACE_0_NAME);

	if (device_reference != NULL && alt_up_sd_card_is_Present() && alt_up_sd_card_is_FAT16()) {

					handle = alt_up_sd_card_fopen(file_name,0);
					if(handle==-1){
						printf("Invalid file\n");
					}
					printf("Reading started\n");

					k=0;
					while(k<file_size){
						*(temp_audio+k)=(char)alt_up_sd_card_read(handle);
						k++;
					}
					alt_up_sd_card_fclose(handle);

					printf("Reading completed & concatenation started\n");

					n=0;
					for(m=0;m<file_size;m+=2){
						*(audio_buffer+n) = *(temp_audio+(m+1));
						*(audio_buffer+n) = *(audio_buffer+n)<< 8;
						*(audio_buffer+n)+= *(temp_audio+m);
						n++;
					}
					free(temp_audio);
	}
	return audio_buffer;

}

void play_loop(unsigned int* audio_buffer,alt_up_audio_dev* audio, int file_to_loop){
	int number_read_l, number_read_r,samples_write_l,samples_write_r;
	int file_size;
	char* file_name;
	number_read_l=0;
	number_read_r=0;
	samples_write_l=15;
	samples_write_r=15;

	switch(file_to_loop){
	case 0: file_size = FILESIZEOF_TITLE;
			file_name = "title.wav";
			break;
	case 1: file_size = FILESIZEOF_VICTORY;
			file_name = "first.wav";
			break;
	case 2: file_size = FILESIZEOF_VICTORY;
			file_name = "second.wav";
			break;
	case 3: file_size = FILESIZEOF_VICTORY;
			file_name = "third.wav";
			break;
	case 9: file_size = FILESIZEOF_GAMEOVER;
			file_name = "gameover.wav";
			break;
	case 99: file_size = FILESIZEOF_VICTORY;
			file_name = "victory.wav";
			break;
	}

	while(samples_write_l>0 && samples_write_r>0){
		number_read_l = alt_up_audio_write_fifo(audio, audio_buffer+tracker_l, samples_write_l, ALT_UP_AUDIO_LEFT);
		number_read_r = alt_up_audio_write_fifo(audio, audio_buffer+tracker_r, samples_write_r, ALT_UP_AUDIO_RIGHT);
		tracker_l+=number_read_l;
		tracker_r+=number_read_l;
		samples_write_l-=number_read_l;
		samples_write_r-=number_read_r;
	}
	if((tracker_l >= (file_size/2)) || (tracker_r >= (file_size/2))){
		tracker_l=22;
		tracker_r=22;
	}

}

void play_once(unsigned int* audio_buffer,alt_up_audio_dev* audio, int file_to_play){
	int number_read_l, number_read_r;
	int file_size;
	char* file_name;
	number_read_l=0;
	number_read_r=0;

	switch(file_to_play){
	case 0: file_size = FILESIZEOF_TITLE;
			file_name = "title.wav";
			break;
	case 1: file_size = FILESIZEOF_VICTORY;
			file_name = "first.wav";
			break;
	case 2: file_size = FILESIZEOF_VICTORY;
			file_name = "second.wav";
			break;
	case 3: file_size = FILESIZEOF_VICTORY;
			file_name = "third.wav";
			break;
	case 9: file_size = FILESIZEOF_GAMEOVER;
			file_name = "gameover.wav";
			break;
	case 99: file_size = FILESIZEOF_VICTORY;
			file_name = "victory.wav";
			break;
	}

	while((tracker_l < file_size/2) && (tracker_r < file_size/2)){
		number_read_l = alt_up_audio_write_fifo(audio, audio_buffer+tracker_l, 50, ALT_UP_AUDIO_LEFT);
		number_read_r = alt_up_audio_write_fifo(audio, audio_buffer+tracker_r, 50, ALT_UP_AUDIO_RIGHT);
		tracker_l+=number_read_l;
		tracker_r+=number_read_r;
	}
	tracker_l=22;
	tracker_r=22;

}
