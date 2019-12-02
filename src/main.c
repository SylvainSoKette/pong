#include "render.h"
#include "utils.h"
#include "game.h"

typedef struct {
    void (*func)(void);
} UnTruc;

void the_test()
{
    printf("Ola struct !\n");
} 

int main(int argc, char **argv)
{
    UnTruc truc;
    truc.func = &the_test;
    truc.func();

    SDL_Window   *window;
    SDL_Renderer *renderer;

    init_SDL_window_and_renderer(&window, &renderer);

    start_game(renderer);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    return EXIT_SUCCESS;
}
