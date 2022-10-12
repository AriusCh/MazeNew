#pragma once

#include <memory>

class dungeon;

class game {
public:
    game();

    void start();
private:

    std::shared_ptr<dungeon> Dungeon;
};
