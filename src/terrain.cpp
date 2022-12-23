#include "terrain.h"

#include <map>

using enum terrainType;

struct fields {
    std::string stringForm;
    bool isWalkable;
};
// A map to easily get chars
static std::map<terrainType, fields> typeTable = {
        {Wall, {"#", false}},
        {Ground, {".", true}}
};

Terrain::Terrain(terrainType type) : type(type) {
    auto tmp = typeTable[type];
    stringForm = tmp.stringForm;
    isWalkable = tmp.isWalkable;
}

std::string Terrain::getStringForm() const {
    return stringForm;
}

Terrain::~Terrain() = default;

bool Terrain::getIsWalkable() const {
    return isWalkable;
}
