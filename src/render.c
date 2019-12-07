#include "render.h"

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

void clean_SDL_window_and_renderer(SDL_Window **w, SDL_Renderer **r)
{
    SDL_DestroyRenderer(*r);
    SDL_DestroyWindow(*w);   
}

void prepare_render(SDL_Renderer *r)
{
    SDL_SetRenderDrawColor(r, 40, 40, 40, 255);
    SDL_RenderClear(r);
}

void end_render(SDL_Renderer *r)
{
    SDL_RenderPresent(r);
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

void draw_score(SDL_Renderer *r, int x, int y, u32 score, Color c)
{
    bool bit;

    const u8 scale = 8;
    const u8 width = 4;
    const u8 height = 8;

    for (u8 j = 0; j < height; j++)
    {
        for (u8 i = 0; i < width; i++)
        {
            bit = get_bit_at_index(NUMBERS[score % 10], 31 - (width * j + i));
            if (bit) {
                draw_rect(
                    r,
                    x + (i * scale),
                    y + (j * scale),
                    scale,
                    scale,
                    c
                );
            }
        }
    }
}

void render_score(SDL_Renderer *r, Game *game)
{
    Color color = game->ball->color;

    draw_score(r, WINDOW_WIDTH / 2 - 64, 16, game->lscore, color);
    draw_score(r, WINDOW_WIDTH / 2 + 32, 16, game->rscore, color);
}
