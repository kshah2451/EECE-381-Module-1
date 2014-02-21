#include "save_game.h"

void save_level(char level){
	short int handle;
	alt_up_sd_card_dev *device_reference = NULL;
	device_reference = alt_up_sd_card_open_dev(ALTERA_UP_SD_CARD_AVALON_INTERFACE_0_NAME);

	if (device_reference != NULL && alt_up_sd_card_is_Present() && alt_up_sd_card_is_FAT16()) {
		handle = alt_up_sd_card_fopen("saves.txt",0); //opens text file to hold our save data
		if (handle==-1){
					printf("ITS BAD\n");
				}

		/*

		char temp[4];
		if (handle==-1){
			printf("ITS BAD\n");
		}
		sprintf(temp,"%d",level);
		if(!alt_up_sd_card_write(handle, temp[0])){
			printf("NOT WORKING\n");
		}
		alt_up_sd_card_write(handle, temp[2]);
		alt_up_sd_card_write(handle, temp[3]);
		alt_up_sd_card_write(handle, temp[4]);*/
		alt_up_sd_card_write(handle,level); //writes level to text file
		alt_up_sd_card_fclose(handle);//closes text file to hold our save data
	}
}

char load_save(void){
	char temp = '0';
	short int handle = alt_up_sd_card_fopen("saves.txt",0); //opens text file holding our save data
	if(handle < 0){ //When no save file exists
		printf("No saves on file\n");
	}
	else{
		temp = alt_up_sd_card_read(handle); //otherwise reads from text file
	}
	return temp;//returns a character indicating level, returns 0 if no saves
}
