#include "render.h"

const u32 WINDOW_WIDTH = 480;
const u32 WINDOW_HEIGHT = 270;
const u32 WINDOW_FLAGS =
//    SDL_WINDOW_FULLSCREEN |
    SDL_WINDOW_SHOWN |
    SDL_WINDOW_OPENGL |
    SDL_WINDOW_BORDERLESS;
const char *GAME_TITLE = "Pong";

void init_SDL_window_and_renderer(SDL_Window **w, SDL_Renderer **r)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    *w = SDL_CreateWindow(
        GAME_TITLE,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        WINDOW_FLAGS
    );

    *r = SDL_CreateRenderer(*w, -1, SDL_RENDERER_SOFTWARE);

    SDL_ShowCursor(SDL_DISABLE);
}

void draw_rect(SDL_Renderer *r, int x, int y, int w, int h, Color c)
{
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
    for (int dy = y; dy < y + h; dy++)
    {
        for (int dx = x; dx < x + w; dx++)
        {
            SDL_RenderDrawPoint(r, dx, dy);
        }
    }
}

void render_terrain(SDL_Renderer *r, Color c)
{
    draw_rect(
        r,
        (WINDOW_WIDTH / 2) - 2,
        0,
        4,
        WINDOW_HEIGHT,
        c
    );
}

void render_entity(SDL_Renderer *r, Entity e)
{
    draw_rect(r, (int)(e.x), (int)(e.y), e.w, e.h, e.color);
}

void render_hud(SDL_Renderer *r, Color c)
{

}
