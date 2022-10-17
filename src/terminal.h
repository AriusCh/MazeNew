#pragma once

#include <memory>

class dungeon;
class cell;

namespace terminal {
    void initialize();
    void restore();
    void delay(int milSec);
    void print(const std::shared_ptr<dungeon> &Dungeon);
    void printCell(const std::shared_ptr<cell>& cell);
    void clearScreen();
    void refreshScreen();
    int getKey();
}
