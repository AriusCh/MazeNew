#pragma once

#include <memory>

class dungeon;

class game {
public:
    game();

    void start();
private:
    void processGameplayInput();
    void movePlayer(int key);
    void openInventory();
    void attackMelee();

    std::shared_ptr<dungeon> Dungeon;
};
