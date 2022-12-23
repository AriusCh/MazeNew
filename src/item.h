#pragma once

#include <string>

enum class ItemType {
    Weapon,
    Armor
};

class Item {
public:
    Item(ItemType type, std::string name);

    ~Item();

    std::string getName() const;

    ItemType getType() const;

protected:
    ItemType type;
    std::string name;
};
