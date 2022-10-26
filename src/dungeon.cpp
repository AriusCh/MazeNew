#include "dungeon.h"

#include "cell.h"
#include "terrain.h"
#include "character.h"
#include "player.h"
#include "item.h"

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::make_unique;

using enum terrainType;

dungeon::dungeon() : level(height, vector<shared_ptr<cell>>(width)) {
    generateEmptyLevel();
}

const vector<vector<shared_ptr<cell>>> &dungeon::getLevel() const {
    return level;
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
    level[height / 2][width / 2]->setCharacter(player::getPlayer());
    addCharacter(player::getPlayer());
    player::getPlayer()->addItem({itemType::Weapon, "Dagger"});

    auto frog = make_shared<character>("Frog", 'f');
    level[1][1]->setCharacter(frog);
    addCharacter(frog);
}

void dungeon::addCharacter(shared_ptr<character> Char) {
    characters.push_back(Char);
}

std::shared_ptr<cell> dungeon::getCellAt(Coords_t coords) const {
    if (coords.y >= height || coords.y < 0 || coords.x >= width || coords.x < 0)
        return nullptr;
    return level[coords.y][coords.x];
}

// newCoords are set relatively to the current position
void dungeon::tryToMove(Coords_t from, Coords_t to) {
    auto fromCell = getCellAt(from);
    auto toCell = getCellAt(to);

    if (!checkMove(fromCell, toCell))
        return;

    auto Char = fromCell->MoveCharacter();
    toCell->setCharacter(Char);
}

bool dungeon::checkMove(std::shared_ptr<cell> fromCell, std::shared_ptr<cell> toCell) {
    if (!fromCell || !toCell)
        return false;

    if (toCell->getCharacter())
        return false;

    if (!toCell->isWalkable())
        return false;

    return true;
}

int dungeon::getHeight() const {
    return height;
}

int dungeon::getWidth() const {
    return width;
}

void dungeon::tryToAttackMelee(std::shared_ptr<character> attacker, Coords_t direction) {
    auto defender = level[direction.y][direction.x]->getCharacter();

    if (!defender)
        return;

    int damage = attacker->calculateDamage();
    defender->damageHealthPoints(damage);

    if (defender->getHealthPoints() <= 0) {
        defender->getCell()->setCharacter(nullptr);
    }
}

dungeon::~dungeon() = default;
