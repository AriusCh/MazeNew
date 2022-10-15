#pragma once

#include "character.h"

#include <memory>

class player : public character{
public:
    player(player &other) = delete;
    void operator=(const player &other) = delete;

    static std::shared_ptr<player> getPlayer();

private:
    player();

    static std::shared_ptr<player> Player;
};