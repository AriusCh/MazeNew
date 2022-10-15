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

terrain::terrain(terrainType type) : type(type) {
    auto tmp = typeTable[type];
    charForm = tmp.charForm;
    isWalkable = tmp.isWalkable;
}

char terrain::getCharForm() const {
    return charForm;
}

terrain::~terrain() {

}

bool terrain::getIsWalkable() const {
    return isWalkable;
}
