#include "screen.h"
#include "dungeon.h"
#include "cell.h"

#include <ctime>
#include <iostream>

int delayMilSec = 30;

void screen::delay(int milSec) {
    milSec *= 1000;
    auto startTime = clock();
    while (clock() < startTime + milSec) ;
}

void screen::print(const dungeon& Dungeon) {
    screen::clear();

    auto level = Dungeon.getLevel();
    for (auto row : level) {
        for (auto col : row) {
            std::cout << col->getStringForm();
        }
        std::cout << '\n';
    }

    screen::delay(delayMilSec);
}

void screen::clear() {
    std::cout << "\e[2J\e[H";
}