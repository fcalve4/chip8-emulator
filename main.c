#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "SDL2/SDL.h"
#include "chip8.h"

#define MEMORY_SIZE 4096

int load_rom(char* f, uint8_t* memory)
{
	FILE* file_ptr = fopen(f, "rb");
	
	if(file_ptr == NULL) {
		fprintf(stderr,"Unable to open open file \n");\
        return 1;
	}	
	
    // Get the size of the file
	fseek(file_ptr, 0, SEEK_END);
	int file_size = ftell(file_ptr); 
	fseek(file_ptr, 0, SEEK_SET);

    if (file_size > MEMORY_SIZE - 0x200) {
        fprintf(stderr, "ROM too large\n");
        fclose(file_ptr);
        return 1;
    }

    // Read ROM in at +0x200 because thats where the PC will be set
	fread(memory+0x200, sizeof(uint8_t), file_size, file_ptr);
    fclose(file_ptr);
    return 0;
}


int main(int argc, char** argv) {

    // Args check
    if (argc < 2) {
		printf("Usage: ./<executable> <rom> \n");
		return 1;
	}


    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Texture* screen;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "SDL_Init FAILED: %s\n", SDL_GetError());
		return 0;
	}


    SDL_Event event;
    window = SDL_CreateWindow(("CHIP-8 Emulator"), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 320, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderSetLogicalSize(renderer, 64, 32);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
    screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,64,32);

    struct chip8_cpu cpu;
    init_chip8_cpu(&cpu);

    if (load_rom(argv[1], cpu.memory) != 0) {
        fprintf(stderr, "Error loading rom");
        return 1;
    };

    while(cpu.is_running) {
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                cpu.is_running = 0;
                break;
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
					case SDLK_ESCAPE:
                        cpu.is_running = 0;
                        break;
					case SDLK_x:
                        keyboard[0] = 1;
                        break;
					case SDLK_1:
                        keyboard[1] = 1;
                        break;
					case SDLK_2:
                        keyboard[2] = 1;
                        break;
					case SDLK_3:
                        keyboard[3] = 1;
                        break;
					case SDLK_q:
                        keyboard[4] = 1;
                        break;
					case SDLK_w:
                        keyboard[5] = 1;
                        break;
					case SDLK_e:
                        keyboard[6] = 1;
                        break;
					case SDLK_a:
                        keyboard[7] = 1;
                        break;
					case SDLK_s:
                        keyboard[8] = 1;
                        break;
					case SDLK_d:
                        keyboard[9] = 1;
                        break;
					case SDLK_z:
                        keyboard[0xA] = 1;
                        break;
					case SDLK_c:
                        keyboard[0xB] = 1;
                        break;
					case SDLK_4:
                        keyboard[0xC] = 1;
                        break;
					case SDLK_r:
                        keyboard[0xD] = 1;
                        break;
					case SDLK_f:
                        keyboard[0xE] = 1;
                        break;
					case SDLK_v:
                        keyboard[0xF] = 1;
                        break;
					}
            }
            else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
					case SDLK_x:
                        keyboard[0] = 0;
                        break;
					case SDLK_1:
                        keyboard[1] = 0;
                        break;
					case SDLK_2:
                        keyboard[2] = 0;
                        break;
					case SDLK_3:
                        keyboard[3] = 0;
                        break;
					case SDLK_q:
                        keyboard[4] = 0;
                        break;
					case SDLK_w:
                        keyboard[5] = 0;
                        break;
					case SDLK_e:
                        keyboard[6] = 0;
                        break;
					case SDLK_a:
                        keyboard[7] = 0;
                        break;
					case SDLK_s:
                        keyboard[8] = 0;
                        break;
					case SDLK_d:
                        keyboard[9] = 0;
                        break;
					case SDLK_z:
                        keyboard[0xA] = 
                        0;break;
					case SDLK_c:
                        keyboard[0xB] = 
                        0;break;
					case SDLK_4:
                        keyboard[0xC] = 
                        0;break;
					case SDLK_r:
                        keyboard[0xD] = 
                        0;break;
					case SDLK_f:
                        keyboard[0xE] = 
                        0;break;
					case SDLK_v:
                        keyboard[0xF] = 
                        0;break;
					}
            }
        }

        printf("Executing: %04x at 0x%x\n", instruction, cpu.PC);
        cpu.PC += 2;

        execute(&cpu);
    }


    SDL_QUIT;
    return 0;
}