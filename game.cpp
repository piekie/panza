#include <stdio.h>

#include "gamefwd.h"
#include "ExtendedTexture.h"
#include "constants.h"

Game* Game::instance = 0;
GameDestroyer Game::destroyer;
SDL_Window* Game::window = NULL;
SDL_Renderer* Game::renderer = NULL;

ExtendedTexture extendedTexture;

int minerAniN = 20;

SDL_Rect minerAni[20];




GameDestroyer::~GameDestroyer() {
    Game::close();

    delete instance;
}
void GameDestroyer::initialize( Game* p ) {
    instance = p;
}

Game& Game::getInstance() {
    if(!instance)     {
        instance = new Game();
        init();
        destroyer.initialize(instance);
    }
    return *instance;
}

bool Game::init() {
    /* Initializing flag */
    bool success = true;

    /* Initialize SDL */
    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    } else {
        /* Create window */
        window = SDL_CreateWindow("Panza!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if (window == NULL) {
             printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        } else {
            /* Rendering */
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
            if( renderer == NULL ) {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            } else {
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                loadMedia();
            }
        }
    }
    return success;
}

void Game::close() {
    SDL_DestroyWindow(window);
    window = NULL;

    SDL_Quit();
}

void Game::run() {
    /* Run loop flag */
    bool quit = false;
    SDL_Event event;
    int i = 0;
    int x = 200;
    int y = 200;
    while (!quit) {
        /* Handle events on queue */
        while (SDL_PollEvent( &event ) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            /* User presses a key */
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_SPACE:
                    quit = true;
                    break;
                }
            }
            SDL_RenderClear( renderer );

            if (i == 7) y -= 20;
            if (i == 14) y -= 20;

            extendedTexture.render(renderer, x, y, &minerAni[i++]);

            if (i == 20) {
                i = 0;
                y += 40;
            }
            SDL_RenderPresent(renderer);
        }
    }
}

void readMiner() {
    for (int i = 0; i < 7; i++) {
        minerAni[i].w = 40;
        minerAni[i].h = 20;
        minerAni[i].x = i * minerAni[i].w;
        minerAni[i].y = 0;
    }

    for (int i = 7; i < 14; i++) {
        minerAni[i].w = 40;
        minerAni[i].h = 40;
        minerAni[i].x = (i - 7) * minerAni[i].w;
        minerAni[i].y = 20;
    }

    for (int i = 14; i < minerAniN; i++) {
        minerAni[i].w = 40;
        minerAni[i].h = 60;
        minerAni[i].x = (i - 14) * minerAni[i].w;
        minerAni[i].y = 80;
    }
}

bool Game::loadMedia() {
    bool success = true;

    if( !extendedTexture.loadFromFile(renderer, "textures/MinerAni.bmp")) {
        printf( "Failed to load sprite sheet texture!\n" );
        success = false;
    }
    else
    {
        readMiner();
    }
    return success;
}
