#ifndef READ_IMAGE_H_
#define READ_IMAGE_H_

#include <altera_up_sd_card_avalon_interface.h>
#include <stdio.h>
#include <system.h>
#include <stdlib.h>

#define FILE_SIZE 614401
#define ARRAY_SIZE 76800
unsigned int* read_image(void);

#endif /* READ_IMAGE_H_ */
