#pragma once

#include <string>
#include <memory>
#include <list>
#include <array>

#include "weapon.h"

class Cell;
class Item;
class Effect;

class Character : public std::enable_shared_from_this<Character> {
public:
    Character(std::string name, char charForm);

    char getCharForm() const;
    [[nodiscard]] std::shared_ptr<Cell> getCell() const;
    void setCell(const std::shared_ptr<Cell> &cell);
    std::list<std::unique_ptr<Item>>& getInventory();
    void addItem(std::unique_ptr<Item> item);
    int getHealthPoints() const;
    void setHealthPoints(int newHealthPoints);
    void damageHealthPoints(int damage);

    int calculateDamage() const;

    void addEffect(std::unique_ptr<Effect> effect);
    void processEffects();

    void equipItem (std::list<std::unique_ptr<Item>>::iterator item);
    void unequipItem (itemType type);

protected:
    std::string name;
    char charForm;
    std::weak_ptr<Cell> cell;
    std::list<std::unique_ptr<Item>> inventory;
    std::list<std::unique_ptr<Effect>> effects;

    struct Equipment {
        std::unique_ptr<Weapon> weapon;
    } equipment;

    int baseDamage = 4;
    int healthPoints = 10;
};
