#pragma once

enum class terrainType {
    Ground,
    Wall
};

class terrain {
public:
    terrain(terrainType type);
    ~terrain();

    char getCharForm() const;
    bool getIsWalkable() const;

private:
    terrainType type;
    char charForm;
    bool isWalkable;
};