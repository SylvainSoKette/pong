#include "render.h"
#include "utils.h"
#include "game.h"

int main(int argc, char **argv)
{
    SDL_Window   *window;
    SDL_Renderer *renderer;

    init_SDL_window_and_renderer(&window, &renderer);

    start_game(renderer);

    clean_SDL_window_and_renderer(&window, &renderer);
    
    return EXIT_SUCCESS;
}
