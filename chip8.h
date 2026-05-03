#include <stdint.h>
#define MEMORY_SIZE 4096

struct chip8_cpu {

    int is_running;

    uint16_t PC;
    uint8_t sp;
    uint16_t I; 

    uint8_t memory[MEMORY_SIZE];
    uint16_t stack[16];
    uint8_t v[16]; // register array

    uint8_t pixel_array[64 * 32];
    uint8_t keyboard[16];

    uint8_t delay_timer;
    uint8_t sound_timer;
};

void init_chip8_cpu(struct chip8_cpu* cpu);

void execute(struct chip8_cpu* cpu);
