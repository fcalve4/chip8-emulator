#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MEMORY_SIZE 4096

void load_rom(char* f)
{
	FILE* file = fopen(f, "rb");
	
	if(file == NULL) {
		fprintf(stderr,"Unable to open open file \n");
	}	
	
    // Get the size of the file
	fseek(file, 0, SEEK_END);
	int file_size = ftell(file); 
	fseek(file, 0, SEEK_SET);

	fread(memory+0x200, sizeof(uint16_t), file_size, file);
}

void execute() {
    // Grab one instruction
    // Decode
    // Execute
}


int main(int arc, char** argv) {

    uint16_t PC;
    uint16_t sp;
    uint16_t I; 

    uint16_t memory[MEMORY_SIZE];
    uint16_t stack[16];
    uint8_t v[16];

    uint8_t delay_timer;
    uint8_t sound_timer;

    memset(stack,0,16);
	memset(memory,0,4096);
	memset(v,0,16);


    // Fetch
    // Decode
    // Execute
    

    while(1) {
        execute();
    }

    
    return 0;
}