#include "gamefwd.h"

int main(int argc, char *argv[]) {
    Game& game = Game::getInstance();
    game.run();

    return 0;
}
