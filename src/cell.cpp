#include "cell.h"

#include <utility>

#include "terrain.h"
#include "character.h"
#include "object.h"

Cell::~Cell() = default;

Cell::Cell(std::unique_ptr<Terrain> terrain, Coords_t coords) : terrain(std::move(terrain)), coords(coords) {
}

Cell::Cell(terrainType TerrainType, Coords_t coords) : terrain(std::make_unique<Terrain>(TerrainType)), coords(coords) {

}

char Cell::getCharForm() {
    if (character) {
        return character->getCharForm();
    }

    return terrain->getCharForm();
}

void Cell::setCharacter(std::shared_ptr<Character> newChar) {
    if (this->character)
        this->character->setCell(nullptr);
    this->character = std::move(newChar);
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

std::shared_ptr<Character> &&Cell::moveCharacter() {
    character->setCell(nullptr);
    return std::move(character);
}
