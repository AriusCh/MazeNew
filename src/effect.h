#pragma once

#include <string>
#include <memory>

class Character;

class Effect {
public:
    Effect(std::string name, std::weak_ptr<Character> owner, int duration);

    void setOwner(std::weak_ptr<Character> newOwner);
    void process();

    int getDuration() const;

private:
    std::string name;
    std::weak_ptr<Character> owner;

    int duration;
};