#include "chip8.h"

int load_rom(char *f, uint8_t *memory)
{
    FILE *file_ptr = fopen(f, "rb");

    if (file_ptr == NULL)
    {
        fprintf(stderr, "Unable to open open file \n");
        return 1;
    }

    // Get the size of the file
    fseek(file_ptr, 0, SEEK_END);
    int file_size = ftell(file_ptr);
    fseek(file_ptr, 0, SEEK_SET);

    if (file_size > MEMORY_SIZE - 0x200)
    {
        fprintf(stderr, "ROM too large\n");
        fclose(file_ptr);
        return 1;
    }

    // Read ROM in at +0x200 because thats where the PC will be set
    fread(memory + 0x200, sizeof(uint8_t), file_size, file_ptr);
    fclose(file_ptr);
    return 0;
}

void init_chip8_cpu(struct chip8_cpu *cpu)
{
    memset(cpu, 0, sizeof(*cpu));
    cpu->PC = 0x200;
    cpu->is_running = 1;
}

void execute(struct chip8_cpu *cpu)
{
    // fetch next instruction
    uint16_t instruction = cpu->memory[cpu->PC] << 8 | cpu->memory[cpu->PC + 1];
    // printf("Executing: %04x at 0x%x\n", instruction, cpu->PC);
    cpu->PC += 2;

    // decode variables
    uint16_t addr = instruction & 0xFFF; // lower 12 bits
    uint8_t kk = instruction & 0xFF;     // lower 8 bits

    uint8_t x = instruction >> 8 & 0xF; // 2nd nybble
    uint8_t y = instruction >> 4 & 0xF; // 3rd nybble
    uint8_t n = instruction & 0xF;      // 4th nybble

    switch (instruction >> 12)
    { // check most significant bit
    case 0x0:
        switch (kk)
        {
        case 0xE0: // CLS
            memset(cpu->pixel_array, 0, 64 * 32);
            break;
        case 0xEE: // RET
            cpu->sp -= 1;
            cpu->PC = cpu->stack[cpu->sp];

            break;
        }
        break;
    case 0x1: // JP addr
        cpu->PC = addr;
        break;
    case 0x2: // CALL addr
        cpu->stack[cpu->sp] = cpu->PC;
        cpu->sp += 1;
        cpu->PC = addr;
        break;
    case 0x3: // SE Vx, kk
        if (cpu->v[x] == kk)
        {
            cpu->PC += 2;
        }
        break;
    case 0x4: // SNE Vx, kk
        if (cpu->v[x] != kk)
        {
            cpu->PC += 2;
        }
        break;
    case 0x5: // SE Vx, Vy
        if (cpu->v[x] == cpu->v[y])
        {
            cpu->PC += 2;
        }
        break;
    case 0x6: // LD Vx, kk
        cpu->v[x] = kk;
        break;
    case 0x7: // ADD Vx, kk
        cpu->v[x] += kk;
        break;
    case 0x8:
        switch (n)
        {
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
        {
            int i;
            i = (int)(cpu->v[x]) + (int)(cpu->v[y]);
            if (i > 255)
                cpu->v[0xF] = 1;
            else
                cpu->v[0xF] = 0;
            cpu->v[x] = i & 0xFF;
            break;
        }
        case 0x5: // SUB Vx, Vy
            if (cpu->v[x] > cpu->v[y])
            {
                cpu->v[0xF] = 1;
            }
            else
            {
                cpu->v[0xF] = 0;
            }
            cpu->v[x] -= cpu->v[y];
            break;
        case 0x6: // SHR Vx
            cpu->v[0xF] = cpu->v[x] & 1;
            cpu->v[x] >>= 1; // divide by 2
            break;
        case 0x7: // SUBN Vx, Vy
            if (cpu->v[y] > cpu->v[x])
            {
                cpu->v[0xF] = 1;
            }
            else
            {
                cpu->v[0xF] = 0;
            }
            cpu->v[x] = cpu->v[y] - cpu->v[x];
            break;
        case 0xE: // SHL Vx
            cpu->v[0xF] = cpu->v[x] & 1;
            cpu->v[x] <<= 1; // multiply by 2
            break;
        }
        break;
    case 0x9: // SNE Vx, Vy
        if (cpu->v[x] != cpu->v[y])
        {
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
    {
        int random_int = rand() % 256;
        cpu->v[x] = kk & random_int;
        break;
    }
    case 0xD: // Dxyn - DRW Vx, Vy, nybble - (the big one)
    {
        uint16_t sprite_x = cpu->v[x];
        uint16_t sprite_y = cpu->v[y];
        uint16_t height = n;
        uint8_t sprite_byte;

        cpu->v[0xF] = 0; // Clear collision flag

        for (int row = 0; row < height; row++)
        {
            sprite_byte = cpu->memory[cpu->I + row];

            for (int col = 0; col < 8; col++)
            {
                if ((sprite_byte & (0x80 >> col)) != 0)
                {
                    // Calculate screen position
                    int screen_x = sprite_x + col;
                    int screen_y = sprite_y + row;
                    int pixel_index = screen_x + (screen_y * 64);

                    // Collision detection: if pixel already on, set flag
                    if (cpu->pixel_array[pixel_index] == 1)
                    {
                        cpu->v[0xF] = 1;
                    }
                    // Toggle pixel (XOR)
                    cpu->pixel_array[pixel_index] ^= 1;
                }
            }
        }
        break;
    }
    case 0xE:
        switch (kk)
        {
        case 0x9E: // SKP Vx
            if (cpu->keyboard[cpu->v[x]] == 1)
            {
                cpu->PC += 2;
            }
            break;
        case 0xA1: // SKNP Vx
            if (cpu->keyboard[cpu->v[x]] == 0)
            {
                cpu->PC += 2;
            }
            break;
        }
        break;
    case 0xF:
        switch (kk)
        {
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
            cpu->I = cpu->v[x] * 5;
            break;
        case 0x33: // LDD B, Vx
        {
            int temp;
            temp = cpu->v[x];
            cpu->memory[cpu->I] = (temp - (temp % 100)) / 100;
            temp -= cpu->memory[cpu->I] * 100;
            cpu->memory[cpu->I + 1] = (temp - (temp % 10)) / 10;
            temp -= cpu->memory[cpu->I + 1] * 10;
            cpu->memory[cpu->I + 2] = temp;
            break;
        }
        case 0x55: // LD [I], Vx
            for (uint8_t i = 0; i <= x; i++)
            {
                cpu->memory[cpu->I + i] = cpu->v[i];
            }
            break;
        case 0x65: // LD Vx, [I]
            for (uint8_t i = 0; i <= x; i++)
            {
                cpu->v[i] = cpu->memory[cpu->I + i];
            }
            break;
        }
        break;
    }
}

void draw(struct chip8_cpu *cpu, SDL_Renderer *renderer, SDL_Texture *screen)
{

    uint32_t pixels[64 * 32];
    memset(pixels, 0, sizeof(pixels));

    for (int y = 0; y < 32; y++)
    {
        for (int x = 0; x < 64; x++)
        {
            if (cpu->pixel_array[x + (y * 64)] == 1)
            {
                pixels[x + (y * 64)] = UINT32_MAX;
            }
        }
    }

    SDL_UpdateTexture(screen, NULL, pixels, 64 * sizeof(uint32_t));

    SDL_Rect position = {0, 0, 64, 32}; // ← Small rect, SDL scales it
    SDL_RenderCopy(renderer, screen, NULL, &position);
    SDL_RenderPresent(renderer);

}