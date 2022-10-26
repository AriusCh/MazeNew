#include "terrain.h"

#include <map>

using enum terrainType;
using std::map;

struct fields {
    char charForm;
    bool isWalkable;
};
// A map to easily get chars
static map<terrainType, fields> typeTable = {
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

Terrain::~Terrain() {

}

bool Terrain::getIsWalkable() const {
    return isWalkable;
}
