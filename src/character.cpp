#include "character.h"

#include <utility>

#include "item.h"
#include "effect.h"

Character::Character(std::string name, char charForm) : name(std::move(name)), charForm(charForm) {

}

char Character::getCharForm() const {
    return charForm;
}

std::shared_ptr<Cell> Character::getCell() const {
    return cell.lock();
}

void Character::setCell(const std::shared_ptr<Cell> &newCell) {
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
    if (equipment.weapon) {
        return equipment.weapon->getDamage();
    }
    return baseDamage;
}

void Character::damageHealthPoints(int damage) {
    healthPoints -= damage;
}

void Character::addItem(std::unique_ptr<Item> item) {
    inventory.push_back(std::move(item));
}

void Character::equipItem(std::list<std::unique_ptr<Item>>::iterator item) {
    auto type = (*item)->getType();
    unequipItem(type);
    switch (type) {
        case itemType::Weapon:
            equipment.weapon.reset(static_cast<Weapon*>((*item).release()));
            inventory.erase(item);
            break;
        default:
            return;
    }
}

void Character::unequipItem(itemType type) {
    switch (type) {
        case itemType::Weapon:
            if (equipment.weapon) {
                inventory.push_back(std::move(equipment.weapon));
            }
            break;
        default:
            return;
    }
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
