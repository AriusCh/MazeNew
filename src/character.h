#pragma once

#include <string>
#include <memory>

class cell;

class character {
public:
    character(std::string name, std::shared_ptr<cell> Cell);

    char getCharForm() const;
    [[nodiscard]] std::shared_ptr<cell> getCell() const;
    void setCell(std::shared_ptr<cell> Cell);

protected:
    std::string name;
    char charForm;
    std::weak_ptr<cell> Cell;
};
