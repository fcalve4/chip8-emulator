# CHIP-8 Emulator

A CHIP-8 interpreter written in C.


## Why I Built This

<!-- Talk about your motivation here. Examples:
     - Learning how CPUs work at a low level
     - Interest in emulation / retro gaming
     - Practicing C and systems programming
     - Understanding how graphics and input work with SDL2
-->


## What is CHIP-8?

<!-- Brief explanation of CHIP-8. Examples:
     - Interpreted language from the 1970s
     - Originally ran on RCA COSMAC VIP and Telmac 1800
     - 4KB memory, 16 registers, 64x32 display
     - Used to write simple games like Pong, Tetris, Space Invaders
-->


## How It Works

### CPU
- Fetch: Read 2 bytes from memory at PC
- Decode: Break opcode into variables (X, Y, N, KK, NNN)
- Execute: Switch based on opcode and do instruction


### Display

- 64x32 pixel array

### Input

- CHIP-8 has a 16-key hex keypad (0-F)
- Mapped to modern keyboard keys (X, 1-4, Q-R, A-F, Z-V)


### Timers

- Both count down at 60Hz
- delay_timer used for game timing
- sound_timer triggers a beep (not implemented)


## Project Structure

```
chip8-emulator/
├── main.c        # SDL2 setup, main loop, input handling
├── chip8.c       # CPU emulation, draw, execute, load ROM
├── chip8.h       # Structs, constants, function declarations
└── roms/         # Publiclically available CHIP-8 ROM files
```


## Building

```bash
gcc -Wall -Wextra main.c chip8.c -lSDL2 -o chip8
```


## Running

```bash
./chip8 roms/PONG
./chip8 roms/TICTAC
```


## Controls

| CHIP-8 Key | Keyboard |
|-----------|----------|
| 0         | X        |
| 1         | 1        |
| 2         | 2        |
| 3         | 3        |
| 4         | Q        |
| 5         | W        |
| 6         | E        |
| 7         | A        |
| 8         | S        |
| 9         | D        |
| A         | Z        |
| B         | C        |
| C         | 4        |
| D         | R        |
| E         | F        |
| F         | V        |



## Resources

- [CHIP-8 Technical Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM)
- [CHIP-8 Wikipedia](https://en.wikipedia.org/wiki/CHIP-8)
- [SDL2 Wiki](https://wiki.libsdl.org/SDL2/FrontPage)