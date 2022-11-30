#pragma once

#include "item.h"

#include <memory>

class Weapon : public Item {
public:
    Weapon(std::string name, int damage);

    ~Weapon();

    int getDamage() const;
private:
    int damage;
};
