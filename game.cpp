#include <stdio.h>

#include "gamefwd.h"
#include "constants.h"

Game* Game::instance = 0;
GameDestroyer Game::destroyer;
SDL_Window* Game::window = NULL;
SDL_Surface* Game::screenSurface = NULL;

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
            /* Get window surface */
            screenSurface = SDL_GetWindowSurface(window);
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
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);
    SDL_Delay(2000);
}
