#include "terrain.h"

#include <map>

using enum terrainType;

struct fields {
    char charForm;
    bool isWalkable;
};
// A map to easily get chars
static std::map<terrainType, fields> typeTable = {
        {Wall, {'#', false}},
        {Ground, {'.', true}}
};

Terrain::Terrain(terrainType type) : type(type) {
    auto tmp = typeTable[type];
    charForm = tmp.charForm;
    isWalkable = tmp.isWalkable;
}

char Terrain::getCharForm() const {
    return charForm;
}

Terrain::~Terrain() = default;

bool Terrain::getIsWalkable() const {
    return isWalkable;
}
