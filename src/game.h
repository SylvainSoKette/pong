#pragma once

#include <time.h>
#include <math.h>

#include <SDL2/SDL.h>

#include "render.h"


// constants
#define WINDOW_WIDTH     480
#define WINDOW_HEIGHT    270
#define GAME_TITLE       "Pong"
#define TARGET_FRAMERATE 60
extern u32 WINDOW_FLAGS;
extern u32 TARGET_FRAMETIME;
extern u32 NUMBERS[];


// data structures
enum WALL_SIDE {
	LEFT_WALL,
	RIGHT_WALL,
};

typedef struct Keys {
	bool E_KEY;
	bool D_KEY;
	bool UP_KEY;
	bool DOWN_KEY;
} Keys;

typedef struct Entity_ {
	float x;
	float y;
	float dx;
	float dy;
	int   w;
	int   h;
	float speed;
	Color color;
} Entity;

typedef struct Game_ {
	bool    is_running;
	Keys    keys;
	int     lscore;
	int     rscore;
	Entity *lpaddle;
	Entity *rpaddle;
	Entity *ball;
} Game;


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
