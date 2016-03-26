#include "gamefwd.h"
#include "Scenery.h"

int main(int argc, char *argv[]) {
    Scenery& scenery = Scenery::getInstance();
    Game& game = Game::getInstance();

    game.run();

    return 0;
}
