#include "Scenery.h"

#include "constants.h"
#include <cstdio>

Tower* Scenery::towerStack = NULL;
SDL_Rect** Scenery::tRects = NULL;
ExtendedTexture* Scenery::textures = NULL;
Scenery* Scenery::instance = NULL;
int Scenery::tAmount = 1;


    int towersAmount = 1;

Scenery::~Scenery() {
    delete towerStack;
    delete textures;
    delete tRects;
    instance = NULL;
}

Scenery& Scenery::getInstance() {
    if (!instance) {
        instance = new Scenery();
        init();
    }
    return *instance;
}

bool Scenery::init() {
    bool success = true;

    tRects = new SDL_Rect*[tAmount];

    /*TODO: Normal t handling */
    tAmount = 1;

    memoryDeploy();
    loadTextures();

   return success;
}

bool Scenery::memoryDeploy() {
    bool success = true;

    //TRECTS
    for (int i = 0; i < tAmount; i++) {
        tRects[i] = new SDL_Rect[TOWER_TILES];
    }


    //TOWERS
    towerStack = new Tower[1];


    return success;
}

bool Scenery::loadTextures() {
    bool success = true;

    textures = new ExtendedTexture[5];

    int cCode = TCODE_TOWER;

    tRects[cCode] = new SDL_Rect[ TOWER_TILES ];

    if (!textures[ cCode ].loadFromFile(Game::getInstance().renderer, TOWER_PATH)) {
        printf( "Failed to load TOWER sprite sheet texture!\n" );
        success = false;
    } else {
        for (int i = 0; i < TOWER_TILES; i++) {
            tRects[cCode][i].w = TOWER_TILE_W;
            tRects[cCode][i].h = TOWER_TILE_H;
            tRects[cCode][i].x = i * TOWER_TILE_W;
            tRects[cCode][i].y = 0;
        }
    }

    return success;

}

void Scenery::renew(int state) {
    if (state == STATE_LOADING) {
        //if (towerStack[0]) {
            //towerStack[0] = new Tower();
            towerStack[0].deploy();
       // }
    }
}

void Scenery::update(int state) {
    if (state == STATE_LOADING) {
        towerStack[0].x = SCREEN_WIDTH / 2 - TOWER_TILE_W / 2;
        towerStack[0].y = SCREEN_HEIGHT / 2 + TOWER_TILE_H / 2;
        towerStack[0].update();

        SDL_Delay(200);
    }


}

void Scenery::render() {
    for (int i = 0; i < towersAmount; i++) {
        towerStack[i].render();
    }
}
