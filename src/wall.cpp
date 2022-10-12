#include "wall.h"

#include <string>

using enum cellType;

wall::wall(){
    type = Wall;
    stringForm = "\u2593";
}

wall::~wall() = default;
