#pragma once

#ifndef RENDER_H
#define RENDER_H 

#include <SDL2/SDL.h>

#include "utils.h"

extern const u32 WINDOW_WIDTH;
extern const u32 WINDOW_HEIGHT;
extern const u32 WINDOW_FLAGS;
extern const char *GAME_TITLE;

void init_SDL_window_and_renderer(SDL_Window **w, SDL_Renderer **r);
void draw_rect(SDL_Renderer *r, int x, int y, int w, int h, Color c);

void render_terrain(SDL_Renderer *r, Color c);
void render_entity(SDL_Renderer *r, Entity e);
void render_hud(SDL_Renderer *r, Color c);

#endif // RENDER_H
