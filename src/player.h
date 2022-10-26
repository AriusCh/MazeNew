#pragma once

#include "character.h"

#include <memory>

class Player : public Character{
public:
    Player(Player &other) = delete;
    void operator=(const Player &other) = delete;

    static std::shared_ptr<Player> getPlayer();

private:
    Player();

    static std::shared_ptr<Player> player;
};