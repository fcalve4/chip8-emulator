#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "chip8.h"

#define MEMORY_SIZE 4096

void load_rom(char* f, uint8_t* memory)
{
	FILE* file_ptr = fopen(f, "rb");
	
	if(file_ptr == NULL) {
		fprintf(stderr,"Unable to open open file \n");\
        return;
	}	
	
    // Get the size of the file
	fseek(file_ptr, 0, SEEK_END);
	int file_size = ftell(file_ptr); 
	fseek(file_ptr, 0, SEEK_SET);

    if (file_size > MEMORY_SIZE - 0x200) {
        fprintf(stderr, "ROM too large\n");
        fclose(file_ptr);
        return;
    }

    // Read ROM in at +0x200 because thats where the PC will be set
	fread(memory+0x200, sizeof(uint8_t), file_size, file_ptr);
    fclose(file_ptr);
}


int main(int argc, char** argv) {

    if (argc < 2) {
		printf("Usage: ./<executable> <rom> \n");
		return 1;
	}

    struct chip8_cpu cpu;
    init_chip8_cpu(&cpu);

    load_rom(argv[1], cpu.memory);

    while(1) {
        uint16_t instruction = cpu.memory[cpu.PC] << 8 | cpu.memory[cpu.PC+1];
        cpu.PC += 2;

        execute(&cpu, instruction);
    }



    return 0;
}