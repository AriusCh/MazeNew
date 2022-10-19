#pragma once

#include <string>
#include <memory>
#include <vector>

class cell;
class item;

class character {
public:
    character(std::string name, char charForm, std::shared_ptr<cell> Cell);

    char getCharForm() const;
    [[nodiscard]] std::shared_ptr<cell> getCell() const;
    void setCell(std::shared_ptr<cell> Cell);
    std::vector<std::unique_ptr<item>>& getInventory();
    int getHealthPoints() const;
    void setHealthPoints(int newHealthPoints);
    void damageHealthPoints(int damage);

    int calculateDamage() const;

protected:
    std::string name;
    char charForm;
    std::weak_ptr<cell> Cell;
    std::vector<std::unique_ptr<item>> Inventory;

    int baseDamage = 4;
    int healthPoints = 10;
};
