#pragma once

#include <vector>
#include <memory>

class Cell;
class Character;

struct Coords_t;

class Dungeon {
public:
    Dungeon();
    ~Dungeon();

    [[nodiscard]] const std::vector<std::vector<std::shared_ptr<Cell>>>& getLevel() const;
    std::shared_ptr<Cell> getCellAt(Coords_t coords) const;
    void tryToMove(Coords_t from, Coords_t to);
    bool checkMove(std::shared_ptr<Cell> fromCell,std::shared_ptr<Cell> toCell);
    void tryToAttackMelee(std::shared_ptr<Character> attacker, Coords_t direction);
    int getHeight() const;
    int getWidth() const;

private:
    int height = 50;
    int width = 150;
    std::vector<std::vector<std::shared_ptr<Cell>>> level;
    std::vector<std::weak_ptr<Character>> characters;
    void addCharacter(std::shared_ptr<Character> character);

    void generateEmptyLevel();
};
