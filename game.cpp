#include <stdio.h>

#include "gamefwd.h"
#include "ExtendedTexture.h"
#include "constants.h"
#include "Tower.h"
#include "Scenery.h"

Game* Game::instance = NULL;
GameDestroyer Game::destroyer;
SDL_Window* Game::window = NULL;
SDL_Renderer* Game::renderer = NULL;

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

                Scenery::getInstance().renew(STATE_LOADING);

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

    while (!quit) {
        SDL_PumpEvents();

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

            Scenery &scenery = Scenery::getInstance();
            scenery.update(STATE_LOADING);
            scenery.render();

            SDL_RenderPresent(renderer);
        }
    }
}

bool Game::loadMedia() {
    bool success = true;

    return success;
}
