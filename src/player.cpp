#include "player.h"
#include "item.h"

using std::make_shared;
using std::shared_ptr;

shared_ptr<Player> Player::player = nullptr;

Player::Player() : Character("Unnamed", '@') {
}

shared_ptr<Player> Player::getPlayer() {
    if (!player) {
        struct playerMakeSharedEnabler : public Player {}; // To make private constructor visible for std::make_shared
        player = make_shared<playerMakeSharedEnabler>();
    }
    return player;
}
