#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "chip8.h"

void init_chip8_cpu(struct chip8_cpu* cpu) {
    memset(cpu, 0, sizeof(*cpu));
    cpu->PC = 0x200;
}

void execute(struct chip8_cpu* cpu, uint16_t instruction) {
    // decode variables
    uint16_t addr = instruction & 0xFFF; // lower 12 bits
    uint8_t kk = instruction & 0xFF; // lower 8 bits

    uint8_t x = instruction >> 8 & 0xF; // 2nd nybble
    uint8_t y = instruction >> 4 & 0xF; // 3rd nybble
    uint8_t n = instruction & 0xF; // 4th nybble


    switch (instruction >> 12) { // check most significant bit
        case 0x0:
        case 0x1:
        case 0x2:
        case 0x3:
        case 0x4:
        case 0x5:
        case 0x6:
        case 0x7:
        case 0x8:
        case 0x9:
        case 0xA:
        case 0xB:
        case 0xC:
        case 0xD:
        case 0xE:
        case 0xF:
    }


    
}