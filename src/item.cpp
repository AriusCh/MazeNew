#include "item.h"

using enum itemType;
using std::string;

Item::Item(itemType type, string name) : type(type), name(name) {
}

string Item::getName() const {
    return name;
}

Item::~Item() = default;
