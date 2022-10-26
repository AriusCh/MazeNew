#pragma once

#include <memory>

class Dungeon;

class Game {
public:
    Game();

    void start();
private:
    void processGameplayInput();
    void movePlayer(int key);
    void openInventory();
    void attackMelee();

    std::shared_ptr<Dungeon> dungeon;
};
