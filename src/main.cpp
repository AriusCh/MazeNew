#include "game.h"

int main() {
    auto game = Game::getGame();
    game->start();

    return 0;
}
