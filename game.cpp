#include <stdio.h>

#include "gamefwd.h"
#include "constants.h"

Game* Game::instance = 0;
GameDestroyer Game::destroyer;
SDL_Window* Game::window = NULL;
SDL_Surface* Game::screenSurface = NULL;

GameDestroyer::~GameDestroyer() {
    SDL_DestroyWindow(instance->window );
    SDL_Quit();

    delete instance;
}
void GameDestroyer::initialize( Game* p ) {
    instance = p;

    if (SDL_Init( SDL_INIT_VIDEO ) < 0) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    } else {
        instance->window = SDL_CreateWindow("Panza!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if (instance->window == NULL) {
             printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
    }
}

Game& Game::getInstance() {
    if(!instance)     {
        instance = new Game();
        destroyer.initialize(instance);
    }
    return *instance;
}

void Game::run() {
    screenSurface = SDL_GetWindowSurface(window);
    printf(SDL_GetError());
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);
    SDL_Delay(2000);
}
