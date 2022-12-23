#pragma once

#include <memory>

class Dungeon;

class Game {
public:
    Game(const Game &other) = delete;

    void operator=(const Game &other) = delete;

    void start();

    static std::shared_ptr<Game> getGame();

    std::shared_ptr<Dungeon> getDungeon();

    void movePlayer(int key);

    void attackMelee(int direction);

    void setEndSession(bool newValue);
private:
    Game();

    static std::shared_ptr<Game> game;

//    void processGameplayInput();

//    void openInventory();

    bool bEndSession = false;

    std::shared_ptr<Dungeon> dungeon;
};
