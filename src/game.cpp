#include "game.h"

#include "dungeon.h"
#include "screen.h"

using std::make_shared;

game::game() : Dungeon(make_shared<dungeon>()){

}

void game::start(){
    screen::clear();
    Dungeon->print();
}
