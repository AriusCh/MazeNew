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
    void print(const std::shared_ptr<Cell> &cell);

    void openInventory();
    void closeInventory();

    void refreshScreen();

    void moveInvCursUp();
    void moveInvCursDown();
    void moveInvPageUp();
    void moveInvPageDown();

    std::string statusLineText = "ABOBABABBABABABBABBABBYAEBALNCURSESQHWIUOEQRIUQHEWUIOEHWQIUEBLYAT";

private:
    Terminal();
    static void initialize();
    static void end();
    static std::shared_ptr<Terminal> term;

    void updateStatusLine();
    void updateWindowSizes();

    class WIN {
    public:
        void moveCurs(int Y, int X) const;
        void print(const std::string& str) const;
        void mvprint(int Y, int X, const std::string &str) const;
        void clear() const;

        int sizeY;
        int sizeX;
        int startY;
        int startX;
    };

    int invSizeY = 30;
    int invSizeX = 30;

    std::unique_ptr<WIN> createWindow(int sizeY, int sizeX, int startY, int startX) const;
    void refreshInventory();

    std::unique_ptr<WIN> winMain = nullptr;
    std::unique_ptr<WIN> winInventory = nullptr;
    std::unique_ptr<WIN> winStatusLine = nullptr;

    int invCursPos = 0;
    int invCurrentPage = 0;
    int invMaxPage;
    int invMaxPageSize;
    const int invTopIndent = 1;
    const int invBottomIndent = 2;
    const int invLeftIndent = 1;
    const int invRightIndent = 1;

    int prevLines = 0;
    int prevCols = 0;
};