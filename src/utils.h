#pragma once

#ifndef UTILS_H
#define UTILS_H

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

typedef struct {
    bool E_KEY;
    bool D_KEY;
    bool UP_KEY;
    bool DOWN_KEY;
} Keys;

typedef struct {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

typedef struct {
    float x;
    float y;
    float dx;
    float dy;
    int   w;
    int   h;
    float speed;
    Color color;
} Entity;

#endif // UTILS_H
