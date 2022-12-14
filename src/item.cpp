#include "item.h"

#include <utility>

using enum ItemType;

Item::Item(ItemType type, std::string name) : type(type), name(std::move(name)) {
}

std::string Item::getName() const {
    return name;
}

ItemType Item::getType() const {
    return type;
}

Item::~Item() = default;
