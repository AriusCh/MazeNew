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

void terminal::print(const std::shared_ptr<dungeon> &Dungeon) {
    terminal::clearScreen();
    auto level = Dungeon->getLevel();
    int terminalHeight = LINES;
    int terminalWidth = COLS;
    int dungeonHeight = Dungeon->getHeight();
    int dungeonWidth = Dungeon->getWidth();

    int startY = 0, startX = 0;
    int endY = dungeonHeight, endX = dungeonWidth;
    int moveY = 0, moveX = 0;

    auto playerCoords = player::getPlayer()->getCell()->getCoords();
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

void terminal::printCell(const std::shared_ptr<cell> &Cell) {
    addch(Cell->getCharForm());
}

void terminal::printPlayerInventory() {
    auto& inv = player::getPlayer()->getInventory();
    auto n = inv.size();
    auto it = inv.begin();
    for (int i = 0; i < playerInventorySizeY && it != inv.end(); i++, it++) {
        mvprintw(i, COLS - playerInventorySizeX - 1, "%s", it->getName().c_str());
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