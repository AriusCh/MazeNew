#pragma once

class dungeon;

namespace terminal {
    void initialize();
    void restore();
    void delay(int milSec);
    void print(const dungeon&);
    void clearScreen();
    int getKey();
}
