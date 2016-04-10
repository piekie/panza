#include "gamefwd.h"
#include "Scenery.h"
#include "Log.h"

int main(int argc, char *argv[]) {
    Scenery& scenery = Scenery::getInstance();
    Game& game = Game::getInstance();
    Log& log = Log::getInstance();
    log.i("hello world", "launched");

    game.run();

    return 0;
}
