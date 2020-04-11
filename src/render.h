#pragma once

#ifndef __RENDER_H
#define __RENDER_H 

#include <SDL2/SDL.h>

#include "utils.h"

void init_SDL_window_and_renderer(SDL_Window **w, SDL_Renderer **r);
void clean_SDL_window_and_renderer(SDL_Window **w, SDL_Renderer **r);
void prepare_render(SDL_Renderer *r);
void end_render(SDL_Renderer *r);

void draw_rect(SDL_Renderer *r, int x, int y, int w, int h, Color c);
void draw_number(SDL_Renderer *r, int x, int y, u32 number, Color c);

void draw_terrain(SDL_Renderer *r, Color c);
void draw_entity(SDL_Renderer *r, Entity e);
void draw_score(SDL_Renderer *r, Game *game);

#endif // RENDER_H
