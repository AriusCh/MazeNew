#include "dungeon.h"

#include "cell.h"
#include "ground.h"
#include "wall.h"
#include "screen.h"

using std::vector;
using std::shared_ptr;
using std::make_shared;

dungeon::dungeon() : level(height, vector<shared_ptr<cell>>(width)){
    generateEmptyLevel();
}

const vector<vector<shared_ptr<cell>>>& dungeon::getLevel() const {
    return level;
}

void dungeon::print() {
    screen::print(*this);
}

void dungeon::generateEmptyLevel() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                level[i][j] = make_shared<wall>();
            } else {
                level[i][j] = make_shared<ground>();
            }
        }
    }
}

dungeon::~dungeon() = default;
