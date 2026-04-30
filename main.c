#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#define MEMORY_SIZE 4096

void load_rom(char* f, uint16_t* memory)
{
	FILE* file_ptr = fopen(f, "rb");
	
	if(file_ptr == NULL) {
		fprintf(stderr,"Unable to open open file \n");
	}	
	
    // Get the size of the file
	fseek(file_ptr, 0, SEEK_END);
	int file_size = ftell(file_ptr); 
	fseek(file_ptr, 0, SEEK_SET);

	fread(memory+0x200, sizeof(uint16_t), file_size, file_ptr);
}


int main(int argc, char** argv) {

    if (argc < 2) {
		printf("Usage: ./a.out <rom> \n");
		return 1;
	}

    

    //uint16_t PC;
    //uint16_t sp;
    //uint16_t I; 

    uint16_t memory[MEMORY_SIZE];
    //uint16_t stack[16];
    //uint8_t v[16];

    //uint8_t delay_timer;
    //uint8_t sound_timer;

    load_rom(argv[1], memory);


    return 0;
}