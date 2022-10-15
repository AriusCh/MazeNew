#include "terminal.h"

#include "dungeon.h"
#include "cell.h"
#include "curses.h"

#include <ctime>

int delayMilSec = 30;

void terminal::initialize() {
    initscr(); // Initialize ncurses
    raw(); // Disable control characters (CTRL-C, CTRL-Z, etc.)
    noecho(); // Disable echo (thx cap)
    keypad(stdscr, TRUE); // Enable F-* keys and arrow keys
}

void terminal::restore() {
    endwin(); // Restore normal terminal
}

void terminal::delay(int milSec) {
    milSec *= 1000;
    auto startTime = clock();
    while (clock() < startTime + milSec) ;
}

void terminal::print(const dungeon& Dungeon) {
    auto level = Dungeon.getLevel();
    for (const auto& row : level) {
        for (const auto& col : row) {
            printw("%c", col->getCharForm());
        }
        printw("\n");
    }
    refresh();
}

void terminal::clearScreen() {
    clear();
}

int terminal::getKey() {
    return getch();
}