#pragma once

#include <vector>
#include <list>
#include <memory>

class cell;
class character;

struct Coords_t;

class dungeon {
public:
    dungeon();
    ~dungeon();

    [[nodiscard]] const std::vector<std::vector<std::shared_ptr<cell>>>& getLevel() const;
    void print() const;
    std::shared_ptr<cell> getCellAt(Coords_t coords) const;
    void tryToMoveCharacter(Coords_t from, Coords_t to);
    bool checkMove(std::shared_ptr<cell> fromCell,std::shared_ptr<cell> toCell);

private:
    int height = 50;
    int width = 150;
    std::vector<std::vector<std::shared_ptr<cell>>> level;
    std::list<std::shared_ptr<character>> characters;

    void generateEmptyLevel();
    std::shared_ptr<character> generateCharacter(std::shared_ptr<character> Char);
};
