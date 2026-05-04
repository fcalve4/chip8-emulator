# CHIP-8 Emulator

A CHIP-8 interpreter written in C.

## What is CHIP-8?

CHIP-8 is an interpreted programming language from the 1970s, originally designed for 
home computers like the COSMAC VIP and ETI 660. It has 4KB of memory, 16 registers, 
a 64x32 pixel display, and used a 16-key hexadecimal keypad for input. 

## Why I Built This

CHIP-8 is a common introduction into building emulators. It is simple enough 
to implement but comprehensive enough to cover the core concepts that carry 
over to more complex systems.


## How It Works

### CPU
- Fetch: Read 2 bytes from memory at PC
- Decode: Break opcode into variables (X, Y, N, KK, NNN)
- Execute: Switch based on opcode and do instruction


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
└── roms/         # Publicly available CHIP-8 ROM files
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

An optional `--speed` flag controls the delay in milliseconds between each CPU cycle. Lower is faster, higher is slower. Default is 4ms.

```bash
./chip8 roms/PONG --speed 2    # faster
./chip8 roms/PONG --speed 4    # default
./chip8 roms/PONG --speed 10   # slower
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