#include "game.h"

void handle_event(SDL_Event *event, Keys *keys, bool *running)
{
    switch (event->type)
    {
        SDL_Scancode sc;
        case SDL_QUIT:
            *running = false;
            break;
        case SDL_KEYDOWN:
            sc = event->key.keysym.scancode;
            if      (sc == SDL_SCANCODE_UP)     keys->UP_KEY = true;
            else if (sc == SDL_SCANCODE_DOWN)   keys->DOWN_KEY = true;
            else if (sc == SDL_SCANCODE_E)      keys->E_KEY = true;
            else if (sc == SDL_SCANCODE_D)      keys->D_KEY = true;
            else if (sc == SDL_SCANCODE_ESCAPE) *running = false;
            break;
        case SDL_KEYUP:
            sc = event->key.keysym.scancode;
            if      (sc == SDL_SCANCODE_UP)   keys->UP_KEY = false;
            else if (sc == SDL_SCANCODE_DOWN) keys->DOWN_KEY = false;
            else if (sc == SDL_SCANCODE_E)    keys->E_KEY = false;
            else if (sc == SDL_SCANCODE_D)    keys->D_KEY = false;
        default:
            break;
    }
}

void clamp_paddle_in_game(Entity *paddle)
{
    if (paddle->y < 0)
    {
        paddle->y = 0;
    }    
    if (paddle->y + paddle->h > WINDOW_HEIGHT)
    {    
        paddle->y = WINDOW_HEIGHT - paddle->h;
    }
}

void update_left_paddle(double dt, Keys keys, Entity *paddle)
{
    paddle->dy = 0;

    // deal with inputs
    if (keys.E_KEY) paddle->dy = -dt * paddle->speed;
    if (keys.D_KEY) paddle->dy =  dt * paddle->speed;

    // update position
    paddle->y += paddle->dy;

    clamp_paddle_in_game(paddle);
}

void update_right_paddle(double dt, Keys keys, Entity *paddle)
{
    paddle->dy = 0;

    // input stuff
    if (keys.UP_KEY)   paddle->dy = -dt * paddle->speed;
    if (keys.DOWN_KEY) paddle->dy =  dt * paddle->speed;

    // update position
    paddle->y += paddle->dy;

    clamp_paddle_in_game(paddle);
}

void handle_ball_get_out(Game *game, enum WALL_SIDE side)
{
    Entity *ball = game->ball;

    if (side == LEFT_WALL)
    {
        game->rscore++;
    } else {
        game->lscore++;
    }

    reset_game(game);
    printf("SCORE: %d - %d\n", game->lscore, game->rscore);
}

void update_ball(double dt, Game* game)
{
    Entity *ball = game->ball;
    Entity *lpaddle = game->lpaddle;
    Entity *rpaddle = game->rpaddle; 

    // update position according to speed;
    ball->x += ball->dx * dt;
    ball->y += ball->dy * dt;

    // clamp ball inside game
    if (ball->y < 0)
    {
        ball->y = 0;
        ball->dy = -ball->dy;
    }
    else if ((ball->y + ball->h) > WINDOW_HEIGHT)
    {
        ball->y = WINDOW_HEIGHT - ball->h;
        ball->dy = -ball->dy;
    }

    // collide with left paddle
    if (ball->x < lpaddle->x + lpaddle->w)
    {
        if ( (ball->y > lpaddle->y) &&
             (ball->y + ball->h < lpaddle->y + lpaddle->h) )
        {
            // replace ball
            ball->x = lpaddle->x + lpaddle->w;
            // reverse ball direction
            ball->dx = -ball->dx;
            // transfert paddle energy to ball
            ball->dy += lpaddle->dy * ball->speed * 0.1f;
            // add a little more speed;
            ball->dx += 5.0f;
        }
    }

    // collide with right paddle
    if (ball->x > rpaddle->x - ball->w)
    {
        if ( (ball->y > rpaddle->y) &&
             (ball->y + ball->h < rpaddle->y + rpaddle->h) )
        {
            // replace ball
            ball->x = rpaddle->x - ball->w;
            // reverse ball direction
            ball->dx = -ball->dx;
            // transfer paddle energy to ball
            ball->dy += rpaddle->dy * ball->speed * 0.1f;
            // add a little more speed
            ball->dx -= 5.0f;
        }
    }

    if (ball->x < 0)
        handle_ball_get_out(game, LEFT_WALL);
    else if ((ball->x + ball->w) > WINDOW_WIDTH)
        handle_ball_get_out(game, RIGHT_WALL);
}

void init_paddle(Entity *paddle, float x, float y, Color color)
{
    paddle->x = x;
    paddle->y = y;
    paddle->dx = 0.0f;
    paddle->dy = 0.0f;
    paddle->w = 8;
    paddle->h = 32;
    paddle->speed = 250.0f;
    paddle->color = color;
}

void init_ball(Entity *ball, Color color)
{
    float dx;
    float dy;

    ball->x = WINDOW_WIDTH / 2;
    ball->y = (WINDOW_HEIGHT / 2) - 4.0f;
    ball->w = 8;
    ball->h = 8;
    ball->speed = 100.0f;
    ball->color = color;

    if (rand()%2 == 1)
        dx = ball->speed;
    else
        dx = -ball->speed;

    dy = (rand()%201 - 100) / 100.0f;
    dy = dy * ball->speed;

    ball->dx = dx;
    ball->dy = dy;
}

void game_loop(SDL_Renderer *renderer, Game *game)
{
    SDL_Event event; 
    u32       nowTime;
    u32       lastTime;
    u32       frameTime;
    double    deltaTime;

    nowTime = SDL_GetTicks();
    lastTime = 0;
    deltaTime = 0;

    while (game->is_running)
    {
        // time
        lastTime = nowTime;
        nowTime = SDL_GetTicks();
        frameTime = nowTime - lastTime;
        deltaTime = ((double)(nowTime - lastTime)) / 1000.0;

        // frame limiter
        if (frameTime < TARGET_FRAMETIME)
        {
            SDL_Delay(TARGET_FRAMETIME - frameTime);
        }

        // deltatime limiter in case of long frame
        if (deltaTime > TARGET_FRAMETIME / 1000.0)
        {
            deltaTime = TARGET_FRAMETIME / 1000.0;
        }

        // events
        while (SDL_PollEvent(&event))
        {
            handle_event(&event, &game->keys, &game->is_running); 
        }

        // update
        update_left_paddle(deltaTime, game->keys, game->lpaddle);
        update_right_paddle(deltaTime, game->keys, game->rpaddle);
        update_ball(deltaTime, game);

        // render
        prepare_render(renderer);

        render_score(renderer, game);
        render_terrain(renderer, game->ball->color);
        render_entity(renderer, *game->lpaddle);
        render_entity(renderer, *game->rpaddle);
        render_entity(renderer, *game->ball);

        end_render(renderer);
    }
}

void reset_game(Game *game)
{
    Color color = {
        .r = rand() % 155 + 100,
        .g = rand() % 155 + 100,
        .b = rand() % 155 + 100,
        .a = 255
    };

    init_paddle(
        game->lpaddle,
        8.0f,
        (WINDOW_HEIGHT / 2) - 16.0f,
        color
    );
    init_paddle(
        game-> rpaddle,
        WINDOW_WIDTH - 2 * 8.0f,
        (WINDOW_HEIGHT / 2) - 16.0f,
        color
    );
    init_ball(game->ball, color);
}

void start_game(SDL_Renderer *renderer)
{
    srand(time(NULL));

    Keys keys = {
        .E_KEY = false,
        .D_KEY = false,
        .UP_KEY = false,
        .DOWN_KEY = false
    };

    Entity lpaddle;
    Entity rpaddle;
    Entity ball;

    Game game = {
        .is_running = true,
        .keys    = keys,
        .lscore  = 0,
        .rscore  = 0,
        .lpaddle = &lpaddle,
        .rpaddle = &rpaddle,
        .ball    = &ball
    };
    reset_game(&game);

    game_loop(renderer, &game);
}
