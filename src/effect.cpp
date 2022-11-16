#include "effect.h"

#include "character.h"

Effect::Effect(std::string name, std::weak_ptr<Character> owner, int duration) : name(std::move(name)), owner(std::move(owner)), duration(duration){

}

void Effect::setOwner(std::weak_ptr<Character> newOwner) {
    owner = std::move(newOwner);
}

void Effect::process() {

    duration--;
}

int Effect::getDuration() const {
    return duration;
}
