#pragma once

#include <vector>
#include <memory>

class cell;

class dungeon {
public:
    dungeon();
    ~dungeon();

    [[nodiscard]] const std::vector<std::vector<std::shared_ptr<cell>>>& getLevel() const;
    void print();

private:
    int height = 25;
    int width = 100;
    std::vector<std::vector<std::shared_ptr<cell>>> level;
};
