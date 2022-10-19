#include "character.h"

#include <utility>

#include "item.h"

using std::string;
using std::pair;
using std::shared_ptr;
using std::unique_ptr;
using std::vector;

using
enum itemType;

character::character(string name, char charForm, std::shared_ptr<cell> Cell) : name(std::move(name)), charForm(charForm), Cell(std::move(Cell)) {

}

char character::getCharForm() const {
    return charForm;
}

std::shared_ptr<cell> character::getCell() const {
    return Cell.lock();

}

void character::setCell(shared_ptr<cell> Cell) {
    this->Cell = Cell;
}

vector<unique_ptr<item>>& character::getInventory() {
    return Inventory;
}

int character::getHealthPoints() const {
    return healthPoints;
}

void character::setHealthPoints(int newHealthPoints) {
    this->healthPoints = newHealthPoints;
}

int character::calculateDamage() const{
    return baseDamage;
}

void character::damageHealthPoints(int damage) {
    healthPoints -= damage;
}
