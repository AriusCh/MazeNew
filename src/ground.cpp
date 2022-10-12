#include "ground.h"

//using enum cellType;

ground::ground() {
    type = cellType::Ground;
//    stringForm = "\u2591";
    stringForm = " ";
}

ground::~ground() = default;