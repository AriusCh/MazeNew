#include "item.h"

using enum itemType;
using std::string;

item::item(itemType type, string name) : type(type), name(name) {
}

string item::getName() const {
    return name;
}

item::~item() = default;
