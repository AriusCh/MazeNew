#pragma once

#include "curses.h"
#include <memory>

class Dungeon;
class Cell;

class Terminal {
public:
    Terminal(Terminal &other) = delete;
    void operator=(const Terminal &other) = delete;
    ~Terminal();
    static std::shared_ptr<Terminal> getTerminal();

    void print(const std::shared_ptr<Dungeon> &dungeon);
    void print(const std::shared_ptr<Cell> &cell);

    void openInventory();
    void closeInventory();

private:
    Terminal();
    static void initialize();
    static void end();
    static std::shared_ptr<Terminal> term;

    int invSizeY = 30;
    int invSizeX = 30;

    WINDOW *winInventory;
    WINDOW *winStatusLine;
};