#include "game.h"
#include "terminal.h"

int main() {

    terminal::initialize();

    Game game{};
    game.start();

    terminal::restore();

    return 0;
}
