#pragma once

#include <string>

enum class itemType {
    Weapon,
    Armor
};

class Item {
public:
    Item(itemType type, std::string name);
    ~Item();

    std::string getName() const;

private:
    itemType type;
    std::string name;
};
