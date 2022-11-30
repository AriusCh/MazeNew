#include "item.h"

#include <utility>

using enum itemType;

Item::Item(itemType type, std::string name) : type(type), name(std::move(name)) {
}

std::string Item::getName() const {
    return name;
}

itemType Item::getType() const {
    return type;
}

Item::~Item() = default;
