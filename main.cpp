#include "gamefwd.h"
#include "Scenery.h"
#include "Log.h"

int main(int argc, char *argv[]) {
    Game& game = Game::getInstance();
    Scenery& scenery = Scenery::getInstance();

    game.run();

    return 0;
}
