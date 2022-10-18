#pragma once

#include <string>
#include <memory>
#include <vector>

class cell;
class item;

class character {
public:
    character(std::string name, std::shared_ptr<cell> Cell);

    char getCharForm() const;
    [[nodiscard]] std::shared_ptr<cell> getCell() const;
    void setCell(std::shared_ptr<cell> Cell);
    std::vector<std::unique_ptr<item>>& getInventory();

protected:
    std::string name;
    char charForm;
    std::weak_ptr<cell> Cell;
    std::vector<std::unique_ptr<item>> Inventory;
};
