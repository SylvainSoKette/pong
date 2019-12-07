#pragma once

#ifndef RENDER_H
#define RENDER_H 

#include <SDL2/SDL.h>

#include "utils.h"

#define WINDOW_WIDTH     480
#define WINDOW_HEIGHT    270
#define GAME_TITLE       "Pong"
#define TARGET_FRAMERATE 120

extern u32 WINDOW_FLAGS;
extern u32 TARGET_FRAMETIME;

extern u32 NUMBERS[];

void init_SDL_window_and_renderer(SDL_Window **w, SDL_Renderer **r);
void draw_rect(SDL_Renderer *r, int x, int y, int w, int h, Color c);
void prepare_render(SDL_Renderer *r);
void end_render(SDL_Renderer *r);

void render_terrain(SDL_Renderer *r, Color c);
void render_entity(SDL_Renderer *r, Entity e);
void draw_score(SDL_Renderer *r, int x, int y, u32 score, Color c);
void render_score(SDL_Renderer *r, Game *game);

#endif // RENDER_H
