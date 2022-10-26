#pragma once

enum class terrainType {
    Ground,
    Wall
};

class Terrain {
public:
    Terrain(terrainType type);
    ~Terrain();

    char getCharForm() const;
    bool getIsWalkable() const;

private:
    terrainType type;
    char charForm;
    bool isWalkable;
};