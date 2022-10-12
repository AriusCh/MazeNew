#include "wall.h"

#include <string>

using enum cellType;

wall::wall(){
    type = Wall;
//    stringForm = "\u2593";
    stringForm = "#";
}

wall::~wall() = default;
