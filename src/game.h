#pragma once

#ifndef GAME_H
#define GAME_H

#include <time.h>
#include <math.h>

#include <SDL2/SDL.h>

#include "render.h"
#include "utils.h"

typedef struct {
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

void handle_event(SDL_Event *event, Keys *keys, bool *quit);
void clamp_paddle_in_game(Entity *paddle);
void update_left_paddle(double dt, Keys keys, Entity *paddle);
void update_right_paddle(double dt, Keys keys, Entity *paddle);
void handle_ball_get_out(Game *game, enum WALL_SIDE side);
void update_ball(double dt, Game *game);
void init_paddle(Entity *paddle, float x, float y, Color color);
void init_ball(Entity *ball, Color color);
void game_loop(SDL_Renderer *renderer, Game *game);
void reset_game(Game *game);
void start_game(SDL_Renderer *renderer);

#endif // GAME_H
