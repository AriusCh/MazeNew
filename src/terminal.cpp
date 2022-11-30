#include "terminal.h"

#include "dungeon.h"
#include "cell.h"
#include "curses.h"
#include "player.h"
#include "item.h"

//#include <ctime>

std::shared_ptr<Terminal> Terminal::term = nullptr;

//int delayMilSec = 30;

void Terminal::initialize() {
    setlocale(LC_ALL, "");
    initscr(); // Initialize ncurses
    raw(); // Disable control characters (CTRL-C, CTRL-Z, etc.)
    noecho(); // Disable echo (thx cap)
    keypad(stdscr, TRUE); // Enable F-* keys and arrow keys
    curs_set(0); // Make cursor invisible

    // Init colors
    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();
    init_colors();
}

void Terminal::end() {
    endwin(); // Restore normal terminal
}

Terminal::Terminal() {
    initialize();
    prevLines = LINES;
    prevCols = COLS;
    winMain = createWindow(prevLines - 1, prevCols, 0, 0);
}

Terminal::~Terminal() {
    end();
}

void Terminal::init_colors() {
    init_pair(1, COLOR_RED, COLOR_BLACK);
}

void Terminal::openInventory() {
    winInventory = createWindow(invSizeY, invSizeX, 0, COLS - invSizeX);
    for (int i = 0; i < invSizeY; i++) {
        winInventory->moveCurs(i, 0);
        for (int j = 0; j < invSizeX; j++) {
            if (i == 0) {
                if (j == 0) {
                    winInventory->print("\u250F");
                } else if (j == invSizeX - 1) {
                    winInventory->print("\u2513");
                } else {
                    winInventory->print("\u2501");
                }
            } else if (i == invSizeY - 1) {
                if (j == 0) {
                    winInventory->print("\u2517");
                } else if (j == invSizeX - 1) {
                    winInventory->print("\u251B");
                } else {
                    winInventory->print("\u2501");
                }
            } else if (j == 0 || j == invSizeX - 1) {
                winInventory->print("\u2503");
            } else {
                winInventory->print(" ");
            }
        }
    }
    winInventory->mvprint(0, 1, "INVENTORY");
    invCursPos = invTopIndent;
    invCurrentPage = 0;

    refreshInventory();
//    auto &inv = Player::getPlayer()->getInventory();
//    auto it = inv.begin();
//    for (int i = 1; i < invSizeY - 1 && it != inv.end(); i++, it++) {
//        auto name = it->getName();
//        if (name.length() > invSizeX - 2)
//            name = name.substr(0, invSizeX - 5) + "...";
//        if (i == invCursPos)
//            attron(A_STANDOUT);
//        winInventory->mvprint(i, 1, name);
//        if (i == invCursPos)
//            attroff(A_STANDOUT);
//    }
//    refreshScreen();
}

void Terminal::closeInventory() {
    winInventory->clear();
    winInventory.reset();
    refreshScreen();
}

std::shared_ptr<Terminal> Terminal::getTerminal() {
    if (!term) {
        struct terminalMakeSharedEnabler : public Terminal {
        };
        term = std::make_shared<terminalMakeSharedEnabler>();
    }
    return term;
}

void Terminal::print(const std::shared_ptr<Dungeon> &dungeon) {
    updateWindowSizes();
    winMain->clear();
    const auto &level = dungeon->getLevel();
    int terminalHeight = winMain->sizeY;
    int terminalWidth = winMain->sizeX;
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
        winMain->moveCurs(moveY + i - startY, moveX);
        for (int j = startX; j < endX; j++) {
            print(level[i][j]);
        }
    }
    refreshScreen();
}

void Terminal::print(const std::shared_ptr<Cell> &cell) {
//    win->print(std::to_string(cell->getCharForm()));
    printw("%c", cell->getCharForm());
}

void Terminal::updateStatusLine() {
    if (!winStatusLine) {
        winStatusLine = createWindow(1, COLS, LINES - 1, 0);
    }
    winStatusLine->clear();
    winStatusLine->mvprint(0, 0, statusLineText);
    refreshScreen();
}

void Terminal::refreshScreen() {
    updateWindowSizes();
    refresh();
}

void Terminal::updateWindowSizes() {
    resize_term(0, 0);
    if (prevLines == LINES && prevCols == COLS)
        return;

    prevLines = LINES;
    prevCols = COLS;

    if (winMain) {
        winMain->clear();
        winMain = createWindow(prevLines - 1, prevCols, 0, 0);
    }
    if (winInventory) {
        winInventory->clear();
        openInventory(); // TEMPORARILY
    }
    if (winStatusLine) {
        winStatusLine->clear();
        winStatusLine = createWindow(1, prevCols, prevLines - 1, 0);
    }
    refreshScreen();
}

void Terminal::WIN::moveCurs(int Y, int X) const {
    move(startY + Y, startX + X);
}

void Terminal::WIN::print(const std::string &str) const {
    printw("%s", str.c_str());
}

void Terminal::WIN::mvprint(int Y, int X, const std::string &str) const {
    mvprintw(startY + Y, startX + X, "%s", str.c_str());
}

void Terminal::WIN::clear() const {
    move(startY, startX);
    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
            printw(" ");
        }
    }
}

std::unique_ptr<Terminal::WIN> Terminal::createWindow(int sizeY, int sizeX, int startY, int startX) const {
    auto win = std::make_unique<WIN>();
    win->sizeY = sizeY;
    win->sizeX = sizeX;
    win->startY = startY;
    win->startX = startX;
    return win;
}

void Terminal::moveInvCursUp() {
    invCursPos--;
    if (invCursPos < invTopIndent) {
        invCursPos = invTopIndent;
    }
    refreshInventory();
}

void Terminal::moveInvCursDown() {
    invCursPos++;
    if (invCursPos >= invSizeY - invBottomIndent) {
        invCursPos = invSizeY - invBottomIndent - 1;
    }
    if (invCursPos > invMaxPageSize) {
        invCursPos = invMaxPageSize;
    }
    refreshInventory();
}

void Terminal::moveInvPageUp() {
    invCurrentPage++;
    if (invCurrentPage > invMaxPage) {
        invCurrentPage = invMaxPage;
    }
    refreshInventory();
}

void Terminal::moveInvPageDown() {
    invCurrentPage--;
    if (invCurrentPage < 0) {
        invCurrentPage = 0;
    }
    refreshInventory();
}

void Terminal::refreshInventory() {
    if (!winInventory) {
        openInventory();
        return;
    }

    // print items
    auto &inv = Player::getPlayer()->getInventory();
    auto it = inv.begin();
    invMaxPage = inv.size() / (invSizeY - invTopIndent - invBottomIndent);
    invMaxPageSize = inv.size() % (invSizeY - invTopIndent - invBottomIndent);
    std::advance(it, invCurrentPage * (invSizeY - invBottomIndent - invTopIndent));
    for (int i = invTopIndent; i < invSizeY - invBottomIndent && it != inv.end(); i++, it++) {
        auto name = it->getName();
        // if name is too long, cut it
        if (name.length() > invSizeX - invLeftIndent - invRightIndent)
            name = name.substr(0, invSizeX - invLeftIndent - invRightIndent - 3) + "...";
        if (i == invCursPos) {
            attron(A_STANDOUT);
            winInventory->mvprint(i, invLeftIndent, name);
            attroff(A_STANDOUT);
        } else {
            winInventory->mvprint(i, invLeftIndent, name);
        }
    }

    // print currentPage / maxPage
    winInventory->mvprint(invSizeY - 2, invLeftIndent, std::to_string(invCurrentPage + 1) + " / " + std::to_string(invMaxPage + 1));

    refreshScreen();
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