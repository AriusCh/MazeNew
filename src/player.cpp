#include "player.h"

#include "item.h"
#include "effect.h"

std::shared_ptr<Player> Player::player = nullptr;

Player::Player() : Character("Unnamed", "@") {
}

std::shared_ptr<Player> Player::getPlayer() {
    if (!player) {
        struct playerMakeSharedEnabler : public Player {}; // To make private constructor visible for std::make_shared
        player = std::make_shared<playerMakeSharedEnabler>();
    }
    return player;
}
