#ifndef INCLUDE_SCENERY
#define INCLUDE_SCENERY

#include "Tower.h"
#include "ExtendedTexture.h"
#include <SDL.h>

class Scenery;

class Scenery {
private:
    static bool init();
    static bool memoryDeploy();
    static bool loadTextures();

    static Scenery* instance;
    static Tower* towerStack;

    static int tAmount;
protected:
    Scenery& operator = ( Scenery& );
public:
    ~Scenery();

    static Scenery& getInstance();
    static void update(int);
    static void renew(int);
    static void render();

    static ExtendedTexture* textures;
    static SDL_Rect** tRects;

    static int STATE;
};

#endif // INCLUDE_SCENERY
