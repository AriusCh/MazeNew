#include "character.h"

#include <utility>

#include "item.h"

using std::string;
using std::shared_ptr;
using std::unique_ptr;

using
enum itemType;

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

std::list<Item>& Character::getInventory() {
    return inventory;
}

int Character::getHealthPoints() const {
    return healthPoints;
}

void Character::setHealthPoints(int newHealthPoints) {
    this->healthPoints = newHealthPoints;
}

int Character::calculateDamage() const{
    return baseDamage;
}

void Character::damageHealthPoints(int damage) {
    healthPoints -= damage;
}

void Character::addItem(Item item) {
    inventory.push_back(item);
}
