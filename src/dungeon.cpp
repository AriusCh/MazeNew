#include "dungeon.h"

#include "cell.h"
#include "terrain.h"
#include "terminal.h"
#include "character.h"
#include "player.h"

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::make_unique;

using
enum terrainType;

dungeon::dungeon() : level(height, vector<shared_ptr<cell>>(width)) {
    generateEmptyLevel();
}

const vector<vector<shared_ptr<cell>>> &dungeon::getLevel() const {
    return level;
}

void dungeon::print() const {
    terminal::print(*this);
}

void dungeon::generateEmptyLevel() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Coords_t coords = {i, j};
            std::shared_ptr<cell> Cell;
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                Cell = make_shared<cell>(Wall, coords);
                level[i][j] = Cell;
            } else {
                Cell = make_shared<cell>(Ground, coords);
                level[i][j] = Cell;
            }
        }
    }
    level[height / 2][width / 2]->setCharacter(generateCharacter(player::getPlayer()));
    player::getPlayer()->setCell(level[height / 2][width / 2]);
}

shared_ptr<character> dungeon::generateCharacter(shared_ptr<character> Char) {
    characters.push_back(Char);
    return std::move(Char);
}

std::shared_ptr<cell> dungeon::getCellAt(Coords_t coords) const {
    if (coords.y >= height || coords.x >= width)
        return nullptr;
    return level[coords.y][coords.x];
}

// newCoords are set relatively to the current position
void dungeon::tryToMoveCharacter(Coords_t from, Coords_t to) {
    auto fromCell = getCellAt(from);
    auto toCell = getCellAt(to);

    if (!checkMove(fromCell, toCell))
        return;

    auto Char = fromCell->getCharacter();
    toCell->setCharacter(Char);
    Char->setCell(toCell);
    fromCell->resetCharacter();
}

bool dungeon::checkMove(std::shared_ptr<cell> fromCell, std::shared_ptr<cell> toCell) {
    if (!fromCell || !toCell)
        return false;

    if (!toCell->isWalkable())
        return false;

    return true;
}

dungeon::~dungeon() = default;
