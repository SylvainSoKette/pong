#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>

#define WINDOW_WIDTH     480
#define WINDOW_HEIGHT    270
#define GAME_TITLE       "Pong"
#define TARGET_FRAMERATE 60

typedef uint_least8_t  u8;
typedef uint_least16_t u16;
typedef uint_least32_t u32;
typedef uint_least64_t u64;

typedef int_least8_t  i8;
typedef int_least16_t i16;
typedef int_least32_t i32;
typedef int_least64_t i64;

extern u32 WINDOW_FLAGS;
extern u32 TARGET_FRAMETIME;
extern u32 NUMBERS[];

typedef struct Keys {
    bool E_KEY;
    bool D_KEY;
    bool UP_KEY;
    bool DOWN_KEY;
} Keys;

typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} Color;

typedef struct Entity {
    float x;
    float y;
    float dx;
    float dy;
    int   w;
    int   h;
    float speed;
    Color color;
} Entity;

typedef struct Game {
    bool    is_running;
    Keys    keys;
    int     lscore;
    int     rscore;
    Entity *lpaddle;
    Entity *rpaddle;
    Entity *ball;
} Game;

enum WALL_SIDE {
    LEFT_WALL,
    RIGHT_WALL,
};

int get_bit_at_index(u32 number, u8 index);

#endif // UTILS_H
