#include "utils.h"

u32 WINDOW_FLAGS =
//    SDL_WINDOW_FULLSCREEN |
    SDL_WINDOW_SHOWN |
    SDL_WINDOW_OPENGL |
    SDL_WINDOW_BORDERLESS;
u32 TARGET_FRAMETIME = 1000 / TARGET_FRAMERATE;

u32 NUMBERS [10] = {                    // 32 = 8 rows * 4 width
    0b00001111100110011001100110011111, // 0
    0b00000010011011100010001000101111, // 1
    0b00001111000100011111100010001111, // 2
    0b00001111000100010111000100011111, // 3
    0b00001000100010101010111100100010, // 4
    0b00001111100010001111000100011111, // 5
    0b00001111100010001111100110011111, // 6
    0b00001111000100010010001001000100, // 7
    0b00001111100110011111100110011111, // 8
    0b00001111100110011111000100011111, // 9
};

int get_bit_at_index(u32 number, u8 index)
{
    return (number & (1 << index) ) >> index;
}
