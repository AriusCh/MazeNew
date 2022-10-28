#include "terminal.h"

#include "dungeon.h"
#include "cell.h"
#include "curses.h"
#include "player.h"
#include "item.h"

#include <ctime>

int delayMilSec = 30;
int playerInventorySizeY = 20;
int playerInventorySizeX = 30;

void terminal::initialize() {
    setlocale(LC_ALL, "");
    initscr(); // Initialize ncurses
    raw(); // Disable control characters (CTRL-C, CTRL-Z, etc.)
    noecho(); // Disable echo (thx cap)
    keypad(stdscr, TRUE); // Enable F-* keys and arrow keys
    curs_set(0); // Make cursor invisible
}

void terminal::restore() {
    endwin(); // Restore normal terminal
}

void terminal::delay(int milSec) {
    milSec *= 1000;
    auto startTime = clock();
    while (clock() < startTime + milSec);
}

void terminal::print(const std::shared_ptr<Dungeon> &dungeon) {
    terminal::clearScreen();
    auto level = dungeon->getLevel();
    int terminalHeight = LINES;
    int terminalWidth = COLS;
    int dungeonHeight = dungeon->getHeight();
    int dungeonWidth = dungeon->getWidth();

    int startY = 0, startX = 0;
    int endY = dungeonHeight, endX = dungeonWidth;
    int moveY = 0, moveX = 0;

    auto playerCoords = Player::getPlayer()->getCell()->getCoords();
    if (terminalHeight > dungeonHeight) {
        moveY = (terminalHeight - dungeonHeight) / 2;
    } else {
        startY = std::max(0, playerCoords.y - terminalHeight / 2);
        endY = std::min(dungeonHeight, playerCoords.y + terminalHeight / 2);
        if (startY == 0) {
            endY = terminalHeight;
        }
        if (endY == dungeonHeight) {
            startY = dungeonHeight - terminalHeight;
        }
    }
    if (terminalWidth > dungeonWidth) {
        moveX = (terminalWidth - dungeonWidth) / 2;
    } else {
        startX = std::max(0, playerCoords.x - terminalWidth / 2);
        endX = std::min(dungeonWidth, playerCoords.x + terminalWidth / 2);
        if (startX == 0) {
            endX = terminalWidth;
        }
        if (endX == dungeonWidth) {
            startX = dungeonWidth - terminalWidth;
        }
    }

    for (int i = startY; i < endY; i++) {
        move(moveY + i - startY, moveX);
        for (int j = startX; j < endX; j++) {
            printCell(level[i][j]);
        }
    }
    refreshScreen();
}

void terminal::printCell(const std::shared_ptr<Cell> &cell) {
    addch(cell->getCharForm());
}

void terminal::printPlayerInventory() {
    auto &inv = Player::getPlayer()->getInventory();
    playerInventorySizeY = LINES - 1;
    auto it = inv.begin();


    for (int i = 0; i < playerInventorySizeY; i++) {
        move(i, COLS - playerInventorySizeX);
        for (int j = COLS - playerInventorySizeX; j < COLS; j++) {
            if (i == 0) {
                if (j == COLS - playerInventorySizeX) {
                    printw("\u250F");
                } else if (j == COLS - 1) {
                    printw("\u2513");
                } else {
                    printw("\u2501");
                }
            } else {
                printw(" ");
            }
        }
    }

    for (int i = 1; i < playerInventorySizeY && it != inv.end(); i++, it++) {
        auto name = it->getName();
        if (name.length() > playerInventorySizeX) {
            name = name.substr(0, playerInventorySizeX - 3) + "...";
        }
        mvprintw(i, COLS - playerInventorySizeX, "%s", name.c_str());
    }
    terminal::refreshScreen();
}

void terminal::clearScreen() {
    clear();
}

void terminal::refreshScreen() {
    resize_term(0, 0);
    refresh();
}

int terminal::getKey() {
    return getch();
}