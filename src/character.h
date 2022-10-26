#pragma once

#include <string>
#include <memory>
#include <list>

class Cell;
class Item;

class Character {
public:
    Character(std::string name, char charForm);

    char getCharForm() const;
    [[nodiscard]] std::shared_ptr<Cell> getCell() const;
    void setCell(std::shared_ptr<Cell> cell);
    std::list<Item>& getInventory();
    void addItem(Item item);
    int getHealthPoints() const;
    void setHealthPoints(int newHealthPoints);
    void damageHealthPoints(int damage);

    int calculateDamage() const;

protected:
    std::string name;
    char charForm;
    std::weak_ptr<Cell> cell;
    std::list<Item> inventory;

    int baseDamage = 4;
    int healthPoints = 10;
};
