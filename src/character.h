#pragma once

#include <string>
#include <memory>
#include <list>
#include <array>

#include "weapon.h"

class Cell;
class Item;

class Character {
public:
    Character(std::string name, char charForm);

    char getCharForm() const;
    [[nodiscard]] std::shared_ptr<Cell> getCell() const;
    void setCell(const std::shared_ptr<Cell>& cell);
    std::list<std::unique_ptr<Item>>& getInventory();
    void addItem(std::unique_ptr<Item> item);
    int getHealthPoints() const;
    void setHealthPoints(int newHealthPoints);
    void damageHealthPoints(int damage);

    int calculateDamage() const;

    void equipItem (std::list<std::unique_ptr<Item>>::iterator item);
    void unequipItem (std::unique_ptr<Item> item);

protected:
    std::string name;
    char charForm;
    std::weak_ptr<Cell> cell;
    std::list<std::unique_ptr<Item>> inventory;
    std::unique_ptr<Weapon> equippedWeapon;
    int baseDamage = 4;
    int healthPoints = 10;
};
