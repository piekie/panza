#include "ExtendedTexture.h"
#include "gamefwd.h"
#include "constants.h"
#include <SDL.h>

#ifndef TOWER_INCLUDE
#define TOWER_INCLUDE

class Tower {
public:
    Tower();

    int x;
    int y;

    int getState();

    void deploy();
    void update();
    void close();
    void render();
    bool isDeployed();
private:
    int currentState;

    int currentFrame;


};

#endif // TOWER_INCLUDE
