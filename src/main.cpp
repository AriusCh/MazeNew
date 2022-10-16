#include "game.h"
#include "terminal.h"

int main() {

    terminal::initialize();

    game Game{};
    Game.start();

    terminal::restore();

    return 0;
}
