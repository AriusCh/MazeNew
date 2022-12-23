#pragma once

#include <string>

enum class terrainType {
    Ground,
    Wall
};

class Terrain {
public:
    Terrain(terrainType type);
    ~Terrain();

    std::string getStringForm() const;
    bool getIsWalkable() const;

private:
    terrainType type;
    std::string stringForm;
    bool isWalkable;
};