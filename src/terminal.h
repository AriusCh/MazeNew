#pragma once

#include <memory>

class Dungeon;
class Cell;

namespace terminal {
    void initialize();
    void restore();
    void delay(int milSec);
    void print(const std::shared_ptr<Dungeon> &dungeon);
    void printCell(const std::shared_ptr<Cell>& cell);
    void printPlayerInventory();
    void clearScreen();
    void refreshScreen();
    int getKey();
}
