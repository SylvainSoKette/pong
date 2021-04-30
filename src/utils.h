#pragma once

#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>


typedef uint_least8_t  u8;
typedef uint_least16_t u16;
typedef uint_least32_t u32;
typedef uint_least64_t u64;

typedef int_least8_t  i8;
typedef int_least16_t i16;
typedef int_least32_t i32;
typedef int_least64_t i64;


typedef struct Color {
	u8 r;
	u8 g;
	u8 b;
	u8 a;
} Color;


int get_bit_at_index(u32 number, u8 index);
