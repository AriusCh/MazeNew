#include "player.h"
#include "item.h"

using std::make_shared;
using std::shared_ptr;

shared_ptr<player> player::Player = nullptr;

player::player() : character("Unnamed", '@', nullptr) {
}

shared_ptr<player> player::getPlayer() {
    if (!Player) {
        struct playerMakeSharedEnabler : public player {}; // To make private constructor visible for std::make_shared
        Player = make_shared<playerMakeSharedEnabler>();
    }
    return Player;
}
