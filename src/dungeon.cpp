#include "dungeon.h"

#include "cell.h"
#include "ground.h"
#include "screen.h"

using std::vector;
using std::shared_ptr;
using std::make_shared;

dungeon::dungeon() : level(height, vector<shared_ptr<cell>>(width, make_shared<ground>())){}

const vector<vector<shared_ptr<cell>>>& dungeon::getLevel() const {
    return level;
}

void dungeon::print() {
    screen::print(*this);
}

dungeon::~dungeon() = default;
