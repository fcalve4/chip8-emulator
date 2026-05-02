#define MEMORY_SIZE 4096

struct chip8_cpu {
    uint16_t PC;
    uint8_t sp;
    uint16_t I; 

    uint8_t memory[MEMORY_SIZE];
    uint16_t stack[16];
    uint8_t v[16]; // register array

    uint8_t delay_timer;
    uint8_t sound_timer;
};

void init_chip8_cpu(struct chip8_cpu* cpu);

void execute(struct chip8_cpu* cpu, uint16_t instruction);
