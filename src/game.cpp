#include "game.h"

#include "dungeon.h"
#include "terminal.h"
#include "player.h"
#include "cell.h"
#include "curses.h"

Game::Game() = default;

bool endSession = false;

void Game::start() {
    dungeon = std::make_shared<Dungeon>();
    auto term = Terminal::getTerminal();
    while (!endSession) {
        term->print(dungeon);
        processGameplayInput();
    }
}

void Game::processGameplayInput() {
    auto key = getch();
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

void Game::movePlayer(int key) {
    auto player = Player::getPlayer();
    auto playerCell = player->getCell();
    if (!playerCell)
        return;
    auto coords = playerCell->getCoords();
    switch (key) {
        case '1':
            dungeon->tryToMove(coords, {coords.y + 1, coords.x - 1});
            break;
        case '2':
            dungeon->tryToMove(coords, {coords.y + 1, coords.x});
            break;
        case '3':
            dungeon->tryToMove(coords, {coords.y + 1, coords.x + 1});
            break;
        case '4':
            dungeon->tryToMove(coords, {coords.y, coords.x - 1});
            break;
        case '6':
            dungeon->tryToMove(coords, {coords.y, coords.x + 1});
            break;
        case '7':
            dungeon->tryToMove(coords, {coords.y - 1, coords.x - 1});
            break;
        case '8':
            dungeon->tryToMove(coords, {coords.y - 1, coords.x});
            break;
        case '9':
            dungeon->tryToMove(coords, {coords.y - 1, coords.x + 1});
            break;
    }
}

void Game::attackMelee() {
    auto direction = getch();
    auto player = Player::getPlayer();
    auto playerCell = player->getCell();
    if (!playerCell)
        return;
    auto coords = playerCell->getCoords();
    switch (direction) {
        case '1':
            dungeon->tryToAttackMelee(Player::getPlayer(), {coords.y + 1, coords.x - 1});
            break;
        case '2':
            dungeon->tryToAttackMelee(Player::getPlayer(), {coords.y + 1, coords.x});
            break;
        case '3':
            dungeon->tryToAttackMelee(Player::getPlayer(), {coords.y + 1, coords.x + 1});
        case '4':
            dungeon->tryToAttackMelee(Player::getPlayer(), {coords.y, coords.x - 1});
            break;
        case '6':
            dungeon->tryToAttackMelee(Player::getPlayer(), {coords.y, coords.x + 1});
            break;
        case '7':
            dungeon->tryToAttackMelee(Player::getPlayer(), {coords.y - 1, coords.x - 1});
            break;
        case '8':
            dungeon->tryToAttackMelee(Player::getPlayer(), {coords.y - 1, coords.x});
            break;
        case '9':
            dungeon->tryToAttackMelee(Player::getPlayer(), {coords.y - 1, coords.x + 1});
            break;
    }
}

void Game::openInventory() {
    auto term = Terminal::getTerminal();
    term->openInventory();
    while (true) {
        auto key = getch();
        switch (key) {
            case KEY_UP:
                term->moveInvCursUp();
                break;
            case KEY_DOWN:
                term->moveInvCursDown();
                break;
            case 'i':
            case 27:
                term->closeInventory();
                return;
        }
    }
}
