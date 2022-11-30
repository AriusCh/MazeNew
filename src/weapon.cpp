#include "weapon.h"
#include "item.h"

//using enum itemType;
using std::string;

Weapon::Weapon(string name, int damage) : Item(itemType::Weapon, name), damage(damage) {}

int Weapon::getDamage() const {
    return damage;
}

Weapon::~Weapon() = default;