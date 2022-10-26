#include "game.h"

#include "dungeon.h"
#include "terminal.h"
#include "player.h"
#include "cell.h"
#include "curses.h"

game::game() {

}

bool endSession = false;

void game::start() {
    Dungeon = std::make_shared<dungeon>();
    while (!endSession) {
        terminal::clearScreen();
        terminal::print(Dungeon);
        processGameplayInput();
    }
}

void game::processGameplayInput() {
    auto key = terminal::getKey();
    switch (key) {
        case '1':
        case '2':
        case '3':
        case '4':
        case '6':
        case '7':
        case '8':
        case '9':
            movePlayer(key);
            break;
        case 'a':
            attackMelee();
            break;
        case 'i':
            openInventory();
            break;
        case 'q':
            endSession = true;
            break;
    }
}

void game::movePlayer(int key) {
    auto Player = player::getPlayer();
    auto PlayerCell = Player->getCell();
    if (!PlayerCell)
        return;
    auto coords = PlayerCell->getCoords();
    switch (key) {
        case '1':
            Dungeon->tryToMove(coords, {coords.y + 1, coords.x - 1});
            break;
        case '2':
            Dungeon->tryToMove(coords, {coords.y + 1, coords.x});
            break;
        case '3':
            Dungeon->tryToMove(coords, {coords.y + 1, coords.x + 1});
            break;
        case '4':
            Dungeon->tryToMove(coords, {coords.y, coords.x - 1});
            break;
        case '6':
            Dungeon->tryToMove(coords, {coords.y, coords.x + 1});
            break;
        case '7':
            Dungeon->tryToMove(coords, {coords.y - 1, coords.x - 1});
            break;
        case '8':
            Dungeon->tryToMove(coords, {coords.y - 1, coords.x});
            break;
        case '9':
            Dungeon->tryToMove(coords, {coords.y - 1, coords.x + 1});
            break;
    }
}

void game::attackMelee() {
    auto direction = terminal::getKey();
    auto Player = player::getPlayer();
    auto PlayerCell = Player->getCell();
    if (!PlayerCell)
        return;
    auto coords = PlayerCell->getCoords();
    switch (direction) {
        case '1':
            Dungeon->tryToAttackMelee(player::getPlayer(), {coords.y + 1, coords.x - 1});
            break;
        case '2':
            Dungeon->tryToAttackMelee(player::getPlayer(), {coords.y + 1, coords.x});
            break;
        case '3':
            Dungeon->tryToAttackMelee(player::getPlayer(), {coords.y + 1, coords.x + 1});
        case '4':
            Dungeon->tryToAttackMelee(player::getPlayer(), {coords.y, coords.x - 1});
            break;
        case '6':
            Dungeon->tryToAttackMelee(player::getPlayer(), {coords.y, coords.x + 1});
            break;
        case '7':
            Dungeon->tryToAttackMelee(player::getPlayer(), {coords.y - 1, coords.x - 1});
            break;
        case '8':
            Dungeon->tryToAttackMelee(player::getPlayer(), {coords.y - 1, coords.x});
            break;
        case '9':
            Dungeon->tryToAttackMelee(player::getPlayer(), {coords.y - 1, coords.x + 1});
            break;
    }
}

void game::openInventory() {
    terminal::printPlayerInventory();
    while (true) {
        auto key = terminal::getKey();
        switch (key) {
            case 'i':
                return;
            case 27:
                return;
        }
    }
}
