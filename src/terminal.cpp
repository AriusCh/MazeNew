#include "terminal.h"

#include "dungeon.h"
#include "cell.h"
#include "curses.h"
#include "player.h"
#include "item.h"

#include <ctime>

std::shared_ptr<Terminal> Terminal::term = nullptr;

int delayMilSec = 30;
int playerInventorySizeY = 20;
int playerInventorySizeX = 30;

void Terminal::initialize() {
    setlocale(LC_ALL, "");
    initscr(); // Initialize ncurses
    raw(); // Disable control characters (CTRL-C, CTRL-Z, etc.)
    noecho(); // Disable echo (thx cap)
    keypad(stdscr, TRUE); // Enable F-* keys and arrow keys
    curs_set(0); // Make cursor invisible
}

void Terminal::end() {
    endwin(); // Restore normal terminal
}

Terminal::Terminal() {
    initialize();
    prevLines = LINES;
    prevCols = COLS;
    winMain = newwin(prevLines - 1, prevCols, 0, 0);
    refresh();
}

Terminal::~Terminal() {
    if (winMain)
        delwin(winMain);
    if (winInventory)
        delwin(winInventory);
    if (winStatusLine)
        delwin(winStatusLine);
    end();
}

void Terminal::openInventory() {
    winInventory = newwin(invSizeY, invSizeX, 0, COLS - invSizeX);
    for (int i = 0; i < invSizeY; i++) {
        wmove(winInventory, i, 0);
        for (int j = 0; j < invSizeX; j++) {
            if (i == 0) {
                if (j == 0) {
                    wprintw(winInventory, "\u250F");
                } else if (j == invSizeX - 1) {
                    wprintw(winInventory, "\u2513");
                } else {
                    wprintw(winInventory, "\u2501");
                }
            } else if (i == invSizeY - 1) {
                if (j == 0) {
                    wprintw(winInventory, "\u2517");
                } else if (j == invSizeX - 1) {
                    wprintw(winInventory, "\u251B");
                } else {
                    wprintw(winInventory, "\u2501");
                }
            } else if (j == 0 || j == invSizeX - 1) {
                wprintw(winInventory, "\u2503");
            } else {
                wprintw(winInventory, " ");
            }
        }
    }
    mvwprintw(winInventory, 0, 1, "INVENTORY");

    auto &inv = Player::getPlayer()->getInventory();
    auto it = inv.begin();
    for (int i = 1; i < invSizeY - 1 && it != inv.end(); i++) {
        auto name = it->getName();
        if (name.length() > invSizeX - 2)
            name = name.substr(0, invSizeX - 5) + "...";
        mvwprintw(winInventory, i, 1, "%s", name.c_str());
        it++;
    }
    resize_term(0, 0);
    updateStatusLine();
    wrefresh(winInventory);
}

void Terminal::closeInventory() {
    wclear(winInventory);
    wrefresh(winInventory);
    delwin(winInventory);
    winInventory = nullptr;
}

std::shared_ptr<Terminal> Terminal::getTerminal() {
    if (!term) {
        struct terminalMakeSharedEnabler : public Terminal {};
        term = std::make_shared<terminalMakeSharedEnabler>();
    }
    return term;
}

void Terminal::print(const std::shared_ptr<Dungeon> &dungeon) {
    wclear(winMain);
    updateWindowSizes();
    const auto &level = dungeon->getLevel();
    int terminalHeight;
    int terminalWidth;
    getmaxyx(winMain, terminalHeight, terminalWidth);
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
        wmove(winMain, moveY + i - startY, moveX);
        for (int j = startX; j < endX; j++) {
            print(winMain, level[i][j]);
        }
    }
    wrefresh(winMain);
    updateStatusLine();
}

void Terminal::print(WINDOW *win, const std::shared_ptr<Cell> &cell) {
    wprintw(win, "%c", cell->getCharForm());
}

void Terminal::updateStatusLine() {
    if (!winStatusLine) {
        winStatusLine = newwin(1, COLS, LINES - 1, 0);
    }
    wclear(winStatusLine);
    mvwprintw(winStatusLine, 0, 0, "%s", statusLineText.c_str());
    wrefresh(winStatusLine);
}

void Terminal::refreshScreen() {
    updateWindowSizes();
    if (winMain) {
        wrefresh(winMain);
    }
    if (winInventory) {
        wrefresh(winInventory);
    }
    if (winStatusLine) {
        wrefresh(winStatusLine);
    }
}

void Terminal::updateWindowSizes() {
    resize_term(0, 0);
    if (prevLines == LINES && prevCols == COLS)
        return;

    prevLines = LINES;
    prevCols = COLS;

    if (winMain) {
        wclear(winMain);
        wrefresh(winMain);
        delwin(winMain);
        winMain = newwin(prevLines - 1, prevCols, 0, 0);
    }
    if (winInventory) {
        wclear(winInventory);
        wrefresh(winInventory);
        delwin(winInventory);
        openInventory(); // TEMPORARILY
    }
    if (winStatusLine) {
        wclear(winStatusLine);
        wrefresh(winStatusLine);
        delwin(winStatusLine);
        winStatusLine = newwin(1, prevCols, prevLines - 1, 0);
    }
}

//void terminal::delay(int milSec) {
//    milSec *= 1000;
//    auto startTime = clock();
//    while (clock() < startTime + milSec);
//}
//
//void terminal::print(const std::shared_ptr<Dungeon> &dungeon) {
//    terminal::clearScreen();
//    auto level = dungeon->getLevel();
//    int terminalHeight = LINES;
//    int terminalWidth = COLS;
//    int dungeonHeight = dungeon->getHeight();
//    int dungeonWidth = dungeon->getWidth();
//
//    int startY = 0, startX = 0;
//    int endY = dungeonHeight, endX = dungeonWidth;
//    int moveY = 0, moveX = 0;
//
//    auto playerCoords = Player::getPlayer()->getCell()->getCoords();
//    if (terminalHeight > dungeonHeight) {
//        moveY = (terminalHeight - dungeonHeight) / 2;
//    } else {
//        startY = std::max(0, playerCoords.y - terminalHeight / 2);
//        endY = std::min(dungeonHeight, playerCoords.y + terminalHeight / 2);
//        if (startY == 0) {
//            endY = terminalHeight;
//        }
//        if (endY == dungeonHeight) {
//            startY = dungeonHeight - terminalHeight;
//        }
//    }
//    if (terminalWidth > dungeonWidth) {
//        moveX = (terminalWidth - dungeonWidth) / 2;
//    } else {
//        startX = std::max(0, playerCoords.x - terminalWidth / 2);
//        endX = std::min(dungeonWidth, playerCoords.x + terminalWidth / 2);
//        if (startX == 0) {
//            endX = terminalWidth;
//        }
//        if (endX == dungeonWidth) {
//            startX = dungeonWidth - terminalWidth;
//        }
//    }
//
//    for (int i = startY; i < endY; i++) {
//        move(moveY + i - startY, moveX);
//        for (int j = startX; j < endX; j++) {
//            printCell(level[i][j]);
//        }
//    }
//    refreshScreen();
//}
//
//void terminal::printCell(const std::shared_ptr<Cell> &cell) {
//    addch(cell->getCharForm());
//}
//
//void terminal::printPlayerInventory() {
//    auto &inv = Player::getPlayer()->getInventory();
//    playerInventorySizeY = LINES - 1;
//    auto it = inv.begin();
//
//
//    for (int i = 0; i < playerInventorySizeY; i++) {
//        move(i, COLS - playerInventorySizeX);
//        for (int j = COLS - playerInventorySizeX; j < COLS; j++) {
//            if (i == 0) {
//                if (j == COLS - playerInventorySizeX) {
//                    printw("\u250F");
//                } else if (j == COLS - 1) {
//                    printw("\u2513");
//                } else {
//                    printw("\u2501");
//                }
//            } else {
//                printw(" ");
//            }
//        }
//    }
//
//    for (int i = 1; i < playerInventorySizeY && it != inv.end(); i++, it++) {
//        auto name = it->getName();
//        if (name.length() > playerInventorySizeX) {
//            name = name.substr(0, playerInventorySizeX - 3) + "...";
//        }
//        mvprintw(i, COLS - playerInventorySizeX, "%s", name.c_str());
//    }
//    terminal::refreshScreen();
//}
//
//void terminal::clearScreen() {
//    clear();
//}
//
//void terminal::refreshScreen() {
//    resize_term(0, 0);
//    refresh();
//}
//
//int terminal::getKey() {
//    return getch();
//}