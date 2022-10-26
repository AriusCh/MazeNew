#pragma once

#include <string>
#include <memory>
#include <list>

class cell;
class item;

class character {
public:
    character(std::string name, char charForm);

    char getCharForm() const;
    [[nodiscard]] std::shared_ptr<cell> getCell() const;
    void setCell(std::shared_ptr<cell> Cell);
    std::list<item>& getInventory();
    void addItem(item Item);
    int getHealthPoints() const;
    void setHealthPoints(int newHealthPoints);
    void damageHealthPoints(int damage);

    int calculateDamage() const;

protected:
    std::string name;
    char charForm;
    std::weak_ptr<cell> Cell;
    std::list<item> Inventory;

    int baseDamage = 4;
    int healthPoints = 10;
};
