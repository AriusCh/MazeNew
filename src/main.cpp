#include <iostream>
#include "game.h"
#include "screen.h"
#include "dungeon.h"

int main() {
    game Game{};
    Game.start();

    dungeon Dungeon = {};

    screen::clear();
    screen::print(Dungeon);

    return 0;
}
