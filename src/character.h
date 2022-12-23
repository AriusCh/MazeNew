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
    Character(std::string name, std::string stringForm);

    std::string getStringForm() const;
    [[nodiscard]] std::shared_ptr<Cell> getCell() const;
    void setCell(const std::shared_ptr<Cell> &cell);
    std::list<std::unique_ptr<Item>>& getInventory();
    void addItem(std::unique_ptr<Item> item);
    int getHealthPoints() const;
    void setHealthPoints(int newHealthPoints);
    void damageHealthPoints(int damage);

    int calculateDamage() const;

    void addEffect(std::unique_ptr<Effect>&& effect);
    void processEffects();

    struct Equipment {
        std::unique_ptr<Weapon> weapon;
    };
    void equipItem (std::list<std::unique_ptr<Item>>::iterator item);
    void unEquipItem (ItemType type);
    const Equipment &getEquipment() const;

protected:
    std::string name;
    std::string stringForm;
    std::weak_ptr<Cell> cell;
    std::list<std::unique_ptr<Item>> inventory;
    std::list<std::unique_ptr<Effect>> effects;

    Equipment equipment;

    int baseDamage = 4;
    int healthPoints = 10;
};
