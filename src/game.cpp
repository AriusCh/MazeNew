#include "game.h"

#include "dungeon.h"
#include "terminal.h"
#include "player.h"
#include "cell.h"

game::game() {

}

bool endSession = false;

void game::start() {
    terminal::clearScreen();
    Dungeon = std::make_shared<dungeon>();

    while (!endSession) {
        terminal::clearScreen();
        Dungeon->print();
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
            Dungeon->tryToMoveCharacter(coords, {coords.y + 1, coords.x - 1});
            break;
        case '2':
            Dungeon->tryToMoveCharacter(coords, {coords.y + 1, coords.x});
            break;
        case '3':
            Dungeon->tryToMoveCharacter(coords, {coords.y + 1, coords.x + 1});
            break;
        case '4':
            Dungeon->tryToMoveCharacter(coords, {coords.y, coords.x - 1});
            break;
        case '6':
            Dungeon->tryToMoveCharacter(coords, {coords.y, coords.x + 1});
            break;
        case '7':
            Dungeon->tryToMoveCharacter(coords, {coords.y - 1, coords.x - 1});
            break;
        case '8':
            Dungeon->tryToMoveCharacter(coords, {coords.y - 1, coords.x});
            break;
        case '9':
            Dungeon->tryToMoveCharacter(coords, {coords.y - 1, coords.x + 1});
            break;
    }
}
