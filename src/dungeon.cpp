#include "dungeon.h"

#include "cell.h"
#include "terrain.h"
#include "character.h"
#include "player.h"
#include "effect.h"

Dungeon::Dungeon() : level(height, std::vector<std::shared_ptr<Cell>>(width)) {
    generateEmptyLevel();
}

const std::vector<std::vector<std::shared_ptr<Cell>>> &Dungeon::getLevel() const {
    return level;
}

void Dungeon::generateEmptyLevel() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            Coords_t coords = {i, j};
            std::shared_ptr<Cell> cell;
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                cell = std::make_shared<Cell>(terrainType::Wall, coords);
                level[i][j] = cell;
            } else {
                cell = std::make_shared<Cell>(terrainType::Ground, coords);
                level[i][j] = cell;
            }
        }
    }
    level[height / 2][width / 2]->setCharacter(Player::getPlayer());
    addCharacter(Player::getPlayer());
    Player::getPlayer()->addItem(std::make_unique<Weapon>("Dagger", 6));

    auto frog = std::make_shared<Character>("Frog", "f");
    level[1][1]->setCharacter(frog);
    addCharacter(frog);
}

void Dungeon::addCharacter(std::shared_ptr<Character> character) {
    characters.push_back(character);
}

std::shared_ptr<Cell> Dungeon::getCellAt(Coords_t coords) const {
    if (coords.y >= height || coords.y < 0 || coords.x >= width || coords.x < 0)
        return nullptr;
    return level[coords.y][coords.x];
}

// newCoords are set relatively to the current position
void Dungeon::tryToMove(Coords_t from, Coords_t to) {
    auto fromCell = getCellAt(from);
    auto toCell = getCellAt(to);

    if (!checkMove(fromCell, toCell))
        return;

    auto Char = fromCell->moveCharacter();
    toCell->setCharacter(Char);
}

bool Dungeon::checkMove(std::shared_ptr<Cell> fromCell, std::shared_ptr<Cell> toCell) {
    if (!fromCell || !toCell)
        return false;

    if (toCell->getCharacter())
        return false;

    if (!toCell->isWalkable())
        return false;

    return true;
}

int Dungeon::getHeight() const {
    return height;
}

int Dungeon::getWidth() const {
    return width;
}

void Dungeon::tryToAttackMelee(std::shared_ptr<Character> attacker, Coords_t direction) {
    auto defender = level[direction.y][direction.x]->getCharacter();

    if (!defender)
        return;

    int damage = attacker->calculateDamage();
    defender->damageHealthPoints(damage);

    if (defender->getHealthPoints() <= 0) {
        defender->getCell()->setCharacter(nullptr);
    }
}

Dungeon::~Dungeon() = default;
