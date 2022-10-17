#include "cell.h"

#include <utility>

#include "terrain.h"
#include "character.h"
#include "object.h"

using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;

cell::~cell() = default;

cell::cell(unique_ptr<terrain> Terrain, Coords_t coords) : Terrain(std::move(Terrain)), coords(coords) {
}

cell::cell(terrainType TerrainType, Coords_t coords) : Terrain(make_unique<terrain>(TerrainType)), coords(coords) {

}

char cell::getCharForm() {
    if (Character) {
        return Character->getCharForm();
    }

    return Terrain->getCharForm();
}

void cell::setCharacter(shared_ptr<character> Char) {
    this->Character = Char;
    Character->setCell(shared_from_this());
}

std::shared_ptr<character> cell::getCharacter() const {
    return Character;
}

Coords_t cell::getCoords() const {
    return coords;
}

bool cell::isWalkable() const {
    return Terrain->getIsWalkable();
}

std::shared_ptr<character> &&cell::MoveCharacter() {
    return std::move(Character);
}
