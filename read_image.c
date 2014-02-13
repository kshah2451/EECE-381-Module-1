#include "read_image.h"


unsigned int* read_image(){
	unsigned char* temp;
	unsigned int* image;
	short int handle;
	int k = 0;
	int i = 0;
	temp = calloc (FILE_SIZE , sizeof(char));
	image = calloc (ARRAY_SIZE , sizeof(short int));
	alt_up_sd_card_dev *device_reference = NULL;
	device_reference = alt_up_sd_card_open_dev(ALTERA_UP_SD_CARD_AVALON_INTERFACE_0_NAME);

	if (device_reference != NULL && alt_up_sd_card_is_Present() && alt_up_sd_card_is_FAT16()) {
		handle = alt_up_sd_card_fopen("text2.txt",0);
		while(alt_up_sd_card_read(handle)!=-1){
			*(temp+k)=(char)alt_up_sd_card_read(handle);
			k++;
		}


		k=0;
		i=0;
		while(*(temp+k)!='!'){


			if(*(temp+k)=='0'){
				k++;
				if(*(temp+k)=='x'){
					k++;
					*(image+i) += (*(temp+k));
					*(image+i) = *(image+i) << 4;
					k++;
					*(image+i) += (*(temp+k));
					*(image+i) = *(image+i) << 4;
					k++;
					*(image+i) += (*(temp+k));
					*(image+i) = *(image+i) << 4;
					k++;
					*(image+i) += (*(temp+k));
					i++;
					k+=2;
				}
			}
			printf("%i\n",*(image+i));
			k++;

		}
		if(614300>k){

			printf("Something is wrong.\n");
		}


	}
	free(temp);
	return image;
}
