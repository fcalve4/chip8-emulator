#include "chip8.h"

int main(int argc, char **argv)
{

    // Args check
    if (argc < 2)
    {
        printf("Usage: ./<executable> <rom> \n");
        return 1;
    }

    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Texture *screen;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        fprintf(stderr, "SDL_Init FAILED: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Event event;
    window = SDL_CreateWindow(("CHIP-8 Emulator"), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 320, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    screen = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 64, 32);

    struct chip8_cpu cpu;
    init_chip8_cpu(&cpu);

    if (load_rom(argv[1], cpu.memory) != 0)
    {
        fprintf(stderr, "Error loading rom\n");
        return 1;
    };

    while (cpu.is_running)
    {
        SDL_Delay(2); // default speed of 5 ms?
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                printf("SDL_QUIT detected\n");
                cpu.is_running = 0;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    cpu.is_running = 0;
                    break;
                case SDLK_x:
                    cpu.keyboard[0] = 1;
                    break;
                case SDLK_1:
                    cpu.keyboard[1] = 1;
                    break;
                case SDLK_2:
                    cpu.keyboard[2] = 1;
                    break;
                case SDLK_3:
                    cpu.keyboard[3] = 1;
                    break;
                case SDLK_q:
                    cpu.keyboard[4] = 1;
                    break;
                case SDLK_w:
                    cpu.keyboard[5] = 1;
                    break;
                case SDLK_e:
                    cpu.keyboard[6] = 1;
                    break;
                case SDLK_a:
                    cpu.keyboard[7] = 1;
                    break;
                case SDLK_s:
                    cpu.keyboard[8] = 1;
                    break;
                case SDLK_d:
                    cpu.keyboard[9] = 1;
                    break;
                case SDLK_z:
                    cpu.keyboard[0xA] = 1;
                    break;
                case SDLK_c:
                    cpu.keyboard[0xB] = 1;
                    break;
                case SDLK_4:
                    cpu.keyboard[0xC] = 1;
                    break;
                case SDLK_r:
                    cpu.keyboard[0xD] = 1;
                    break;
                case SDLK_f:
                    cpu.keyboard[0xE] = 1;
                    break;
                case SDLK_v:
                    cpu.keyboard[0xF] = 1;
                    break;
                }
                break;

            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_x:
                    cpu.keyboard[0] = 0;
                    break;
                case SDLK_1:
                    cpu.keyboard[1] = 0;
                    break;
                case SDLK_2:
                    cpu.keyboard[2] = 0;
                    break;
                case SDLK_3:
                    cpu.keyboard[3] = 0;
                    break;
                case SDLK_q:
                    cpu.keyboard[4] = 0;
                    break;
                case SDLK_w:
                    cpu.keyboard[5] = 0;
                    break;
                case SDLK_e:
                    cpu.keyboard[6] = 0;
                    break;
                case SDLK_a:
                    cpu.keyboard[7] = 0;
                    break;
                case SDLK_s:
                    cpu.keyboard[8] = 0;
                    break;
                case SDLK_d:
                    cpu.keyboard[9] = 0;
                    break;
                case SDLK_z:
                    cpu.keyboard[0xA] = 0;
                    break;
                case SDLK_c:
                    cpu.keyboard[0xB] = 0;
                    break;
                case SDLK_4:
                    cpu.keyboard[0xC] = 0;
                    break;
                case SDLK_r:
                    cpu.keyboard[0xD] = 0;
                    break;
                case SDLK_f:
                    cpu.keyboard[0xE] = 0;
                    break;
                case SDLK_v:
                    cpu.keyboard[0xF] = 0;
                    break;
                }
                break;
            }
        }
        if (cpu.delay_timer > 0)
        {
            --cpu.delay_timer;
        }
        execute(&cpu);
        printf("After execute: is_running = %d\n", cpu.is_running);
        draw(&cpu, renderer, screen);
    }

    // cleanup
    SDL_DestroyTexture(screen);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    printf("Main loop exited. is_running = %d\n", cpu.is_running);
    return 0;
}