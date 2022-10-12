#include "game.h"

#include "dungeon.h"
#include "screen.h"

game::game() : Dungeon(std::make_shared<dungeon>()){

}

void game::start() {
    screen::clear();
    Dungeon->print();
}
