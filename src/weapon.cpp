#include "weapon.h"
#include "item.h"

Weapon::Weapon(std::string name, int damage) : Item(itemType::Weapon, std::move(name)), damage(damage) {}

int Weapon::getDamage() const {
    return damage;
}

Weapon::~Weapon() = default;