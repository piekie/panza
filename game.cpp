#include <SDL_ttf.h>

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

bool Game::quit = false;

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
    if (SDL_Init( SDL_INIT_VIDEO ) < 0 || TTF_Init() == -1) {
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
    TTF_Quit();
}

void Game::run() {
    /* Run loop flag */
    quit = false;
    SDL_Event event;

    Scenery &scenery = Scenery::getInstance();

    while (!quit) {
        SDL_PumpEvents();
        int state = scenery.getState();


        /* Handle events on queue */
        while (SDL_PollEvent( &event ) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            /* User presses a key */
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_F4:
                    quit = true;
                    break;
                case SDLK_w:
                    if (state == STATE_MENU || state == STATE_SETTINGS) scenery.menuUp();
                    break;
                case SDLK_s:
                    if (state == STATE_MENU || state == STATE_SETTINGS) scenery.menuDown();
                    break;
                case SDLK_RETURN:
                case SDLK_SPACE:
                    if (state == STATE_MENU || state == STATE_SETTINGS) scenery.menuChoose();
                    break;
                case SDLK_ESCAPE:
                    scenery.goBack();
                    break;
                default:
                    break;
                }
            }
        }
        SDL_RenderClear( renderer );

        scenery.update( scenery.getState() );
        scenery.render();

        SDL_RenderPresent(renderer);
    }
}

bool Game::loadMedia() {
    bool success = true;

    return success;
}

void Game::exit() {
    quit = true;
}
