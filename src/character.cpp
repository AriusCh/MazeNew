#include "character.h"

#include <utility>

#include "item.h"

using std::string;
using std::shared_ptr;
using std::unique_ptr;

//using enum itemType;

Character::Character(string name, char charForm) : name(std::move(name)), charForm(charForm) {

}

char Character::getCharForm() const {
    return charForm;
}

std::shared_ptr<Cell> Character::getCell() const {
    return cell.lock();

}

void Character::setCell(const shared_ptr<Cell> &newCell) {
    this->cell = newCell;
}

std::list<std::unique_ptr<Item>> & Character::getInventory() {
    return inventory;
}

int Character::getHealthPoints() const {
    return healthPoints;
}

void Character::setHealthPoints(int newHealthPoints) {
    this->healthPoints = newHealthPoints;
}

int Character::calculateDamage() const{
    if (equippedWeapon) return equippedWeapon->getDamage();
    return baseDamage;
}

void Character::damageHealthPoints(int damage) {
    healthPoints -= damage;
}

void Character::addItem(std::unique_ptr<Item> item) {
    inventory.push_back(std::move(item));
}

void Character::equipItem(std::list<unique_ptr<Item>>::iterator item) {
    equippedWeapon.reset(static_cast<Weapon*>((*item).release()));
    //equippedWeapon =
    inventory.erase(item);
}

void Character::unequipItem(std::unique_ptr<Item> item) {

}

void Character::addEffect(std::unique_ptr<Effect> effect) {
    effect->setOwner(shared_from_this());
    effects.push_back(std::move(effect));
}

void Character::processEffects() {
    for (auto it = effects.begin(); it != effects.end(); it++) {
        (*it)->process();
        if ((*it)->getDuration() <= 0) {
            effects.erase(it);
        }
    }
}
