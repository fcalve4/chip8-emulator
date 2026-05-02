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
            switch (kk) {
                case 0xE0: // CLS
                case 0xEE: // RET
            }
        case 0x1: // JP addr
            cpu->PC = addr;
            break;
        case 0x2: // CALL addr
            
            
        case 0x3: // SE Vx, kk
            if (cpu->v[x] == kk) {
                cpu->PC += 2;
            }
            break;
        case 0x4: // SNE Vx, kk
            if (cpu->v[x] != kk) {
                cpu->PC += 2;
            }
            break;
        case 0x5: // SE Vx, Vy
            if (cpu->v[x] == cpu->v[y]) {
                cpu->PC +=2;
            }
            break;
        case 0x6: // LD Vx, kk
            cpu->v[x] == kk;
            break;
        case 0x7: // ADD Vx, kk
            cpu->v[x] += kk;
            break;
        case 0x8:
            switch (n) {
                case 0x0: // LD  Vx, Vy
                    cpu->v[x] = cpu->v[y];
                    break;
                case 0x1: // OR  Vx, Vy
                    cpu->v[x] = cpu->v[x] | cpu->v[y];
                    break;
                case 0x2: // AND Vx, Vy
                    cpu->v[x] = cpu->v[x] & cpu->v[y];
                    break;
                case 0x3: // XOR Vx, Vy
                    cpu->v[x] = cpu->v[x] ^ cpu->v[y];
                    break;
                case 0x4: // ADD Vx, Vy
                    int i;
				    i = (int)(cpu->v[x]) + (int)(cpu->v[y]);
				    if (i > 255)
				    	cpu->v[0xF] = 1;
				    else
				    	cpu->v[0xF] = 0;
				    cpu->v[x] = i & 0xFF;
                    break;
                case 0x5: // SUB Vx, Vy
                    if (cpu->v[x] > cpu->v[y]) {
                        cpu->v[0xF] = 1;
                    }
                    else {
                        cpu->v[0xF] = 0;
                    }
                    cpu->v[x] -= cpu->v[y];
                    break;
                case 0x6: // SHR Vx
                    cpu->v[0xF] = cpu->v[x] & 1;
                    cpu->v[x] >>= 1; // divide by 2
                    break;
                case 0x7: // SUBN Vx, Vy
                    if (cpu->v[y] > cpu->v[x]) {
                        cpu->v[0xF] = 1;
                    }
                    else {
                        cpu->v[0xF] = 0;
                    }
                    cpu->v[x] = cpu->v[y] - cpu->v[x];
                    break;
                case 0xE: // SHL Vx
                    cpu->v[0xF] = cpu->v[x] & 1;
                    cpu->v[x] <<= 1; // multiply by 2
                    break;
            }
        case 0x9: // SNE Vx, Vy
            if (cpu->v[x] != cpu->v[y]) {
                cpu->PC += 2;
            }
            break;
        case 0xA: // LD I, addr
            cpu->I = addr;
            break;
        case 0xB: // JP V0, addr
            cpu->PC = addr + cpu->v[0];
            break;
        case 0xC: // RND Vx, byte
            int random_int = rand() % 256;
            cpu->v[x] = kk & random_int;
            break;
        case 0xD: // Dxyn - DRW Vx, Vy, nibble
        case 0xE:
            switch (kk) {
                case 0x9E: // SKP Vx
                case 0xA1: // SKNP Vx
            }
        case 0xF:
            switch (kk) {
                case 0x07: // LD Vx, DT
                    cpu->v[x] = cpu->delay_timer;
                    break;
                case 0x0A: // LD Vx, K
                    break;
                case 0x15: // LD DT, Vx
                    cpu->delay_timer = cpu->v[x];
                    break;
                case 0x18: // LD ST, Vx
                    cpu->v[x] = cpu->sound_timer;
                    break;
                case 0x1E: // ADD I, Vx
                    cpu->I += cpu->v[x];
                    break;
                case 0x29: // LD F, Vx
                    break;
                case 0x33: // LDD B, Vx
                    break;
                case 0x55: // LD [I], Vx
                    break;
                case 0x65: // LD Vx, [I]
                    break;

            }
    }


    
}