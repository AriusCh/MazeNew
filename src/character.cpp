#include "character.h"

#include <utility>

#include "item.h"
#include "effect.h"

using std::string;
using std::shared_ptr;
using std::unique_ptr;

using enum itemType;

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

void Character::addItem(const Item &item) {
    inventory.push_back(item);
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
