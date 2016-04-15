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


    static int STATE;

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
    static int getState();
    static bool loadFonts();

    static ExtendedTexture* textures;
    static ExtendedTexture* titles;
    static SDL_Rect** tRects;

    void menuUp();
    void menuDown();
    void menuChoose();
    void goBack();
};

#endif // INCLUDE_SCENERY
