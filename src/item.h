#pragma once

#include <string>

enum class itemType {
    Weapon,
    Armor
};

class item {
public:
    item(itemType type, std::string name);
    ~item();

    std::string getName() const;

private:
    itemType type;
    std::string name;
};
