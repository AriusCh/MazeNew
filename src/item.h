#pragma once

#include <string>

using std::string;

enum class itemType {
    Weapon,
    Armor
};

class item {
public:
    item(itemType type, string name);
    ~item();

    string getName() const;

private:
    itemType type;
    string name;
};
