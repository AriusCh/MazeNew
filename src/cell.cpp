#include "cell.h"

#include <utility>

#include "terrain.h"
#include "character.h"
#include "object.h"

using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;

Cell::~Cell() = default;

Cell::Cell(unique_ptr<Terrain> terrain, Coords_t coords) : terrain(std::move(terrain)), coords(coords) {
}

Cell::Cell(terrainType TerrainType, Coords_t coords) : terrain(make_unique<Terrain>(TerrainType)), coords(coords) {

}

char Cell::getCharForm() {
    if (character) {
        return character->getCharForm();
    }

    return terrain->getCharForm();
}

void Cell::setCharacter(shared_ptr<Character> character) {
    if (this->character)
        this->character->setCell(nullptr);
    this->character = std::move(character);
    if (!this->character)
        return;
    this->character->setCell(shared_from_this());
}

std::shared_ptr<Character> Cell::getCharacter() const {
    return character;
}

Coords_t Cell::getCoords() const {
    return coords;
}

bool Cell::isWalkable() const {
    return terrain->getIsWalkable();
}

std::shared_ptr<Character> &&Cell::MoveCharacter() {
    character->setCell(nullptr);
    return std::move(character);
}
