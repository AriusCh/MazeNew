#pragma once

#include "curses.h"
#include <memory>
#include <string>

class Dungeon;
class Cell;

class Terminal {
public:
    Terminal(Terminal &other) = delete;
    void operator=(const Terminal &other) = delete;
    ~Terminal();
    static std::shared_ptr<Terminal> getTerminal();

    void print(const std::shared_ptr<Dungeon> &dungeon);
    void print(WINDOW *win, const std::shared_ptr<Cell> &cell);

    void openInventory();
    void closeInventory();

    void refreshScreen();

    std::string statusLineText = "ABOBABABBABABABBABBABBSBSDJASBDKJASDKJHUIQHWIUOEQRIUQHEWUIOEHWQIUEBLYAT";

private:
    Terminal();
    static void initialize();
    static void end();
    static std::shared_ptr<Terminal> term;

    void updateStatusLine();
    void updateWindowSizes();

    int invSizeY = 30;
    int invSizeX = 30;

    WINDOW *winMain = nullptr;
    WINDOW *winInventory = nullptr;
    WINDOW *winStatusLine = nullptr;

    int prevLines = 0;
    int prevCols = 0;
};