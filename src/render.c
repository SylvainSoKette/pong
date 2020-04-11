#include "render.h"

void init_SDL_window_and_renderer(SDL_Window **window,
                                  SDL_Renderer **renderer)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	*window = SDL_CreateWindow(
		GAME_TITLE,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		WINDOW_FLAGS
	);

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_SOFTWARE);

	SDL_ShowCursor(SDL_DISABLE);
}

void clean_SDL_window_and_renderer(SDL_Window **window,
                                   SDL_Renderer **renderer)
{
	SDL_DestroyRenderer(*renderer);
	SDL_DestroyWindow(*window);   
}

void prepare_render(SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
	SDL_RenderClear(renderer);
}

void end_render(SDL_Renderer *renderer)
{
	SDL_RenderPresent(renderer);
}

void draw_rect(SDL_Renderer *renderer,
               int x, int y,
               int w, int h,
               Color c)
{
	SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
	for (int dy = y; dy < y + h; dy++)
	{
		for (int dx = x; dx < x + w; dx++)
		{
			SDL_RenderDrawPoint(renderer, dx, dy);
		}
	}
}

void draw_number(SDL_Renderer *r, int x, int y, u32 number, Color c)
{
	bool bit;
	const u8 scale = 8;
	const u8 width = 4;
	const u8 height = 8;

	for (u8 j = 0; j < height; j++)
	{
		for (u8 i = 0; i < width; i++)
		{
			bit = get_bit_at_index(NUMBERS[number % 10], 31 - (width * j + i));
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

void draw_terrain(SDL_Renderer *renderer, Color c)
{
	draw_rect(
		renderer,
		(WINDOW_WIDTH / 2) - 2, 0,
		4, WINDOW_HEIGHT,
		c
	);
}

void draw_entity(SDL_Renderer *renderer, Entity entity)
{
	draw_rect(
		renderer,
		(int)(entity.x), (int)(entity.y),
		entity.w, entity.h,
		entity.color
	);
}


void draw_score(SDL_Renderer *renderer, Game *game)
{
	Color color = game->ball->color;

	draw_number(renderer, WINDOW_WIDTH / 2 - 64, 16, game->lscore, color);
	draw_number(renderer, WINDOW_WIDTH / 2 + 32, 16, game->rscore, color);
}
