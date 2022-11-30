#pragma once

#include <string>

enum class itemType {
    Weapon,
    Armor
};

class Item {
public:
    Item(itemType type, std::string name);

    Item();

    ~Item();

    std::string getName() const;

    itemType getType() const;

protected:
    itemType type;
    std::string name;
};
