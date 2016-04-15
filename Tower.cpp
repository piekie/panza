#include "Tower.h"
#include "constants.h"
#include "Scenery.h"

Tower::Tower() {
    currentState = TOWER_CLOSED;
    currentFrame = 0;
}

int Tower::getState() {
    return currentState;
}

bool Tower::isDeployed() {
    if (currentState == TOWER_DEPLOYED) {
        return true;
    }
    return false;
}

void Tower::deploy() {
    if (currentState == TOWER_CLOSED ||
        currentState == TOWER_CLOSING) {

        currentState = TOWER_DEPLOYING;
    }
}

void Tower::close() {
    if (currentState == TOWER_DEPLOYED ||
        currentState == TOWER_DEPLOYING) {

        currentState = TOWER_CLOSING;
     }
}

void Tower::update(){
    if (currentState == TOWER_DEPLOYING) {
        currentFrame++;

        if (currentFrame == TOWER_TILES) {
            currentState = TOWER_DEPLOYED;
            currentFrame = TOWER_TILES - 1;
        }
    }

    if (currentState == TOWER_CLOSING) {
        currentFrame--;

        if (currentFrame == 0) {
            currentState = TOWER_CLOSED;
        }
    }

}

void Tower::render() {
    Scenery &scenery = Scenery::getInstance();


    scenery.textures[TCODE_TOWER].render(x, y, &scenery.tRects[TCODE_TOWER][currentFrame]);
}
