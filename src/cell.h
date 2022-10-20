#pragma once

#include <memory>

class terrain;

class object;

class character;

class dungeon;

enum class terrainType;

struct Coords_t {
    int y;
    int x;
};

class cell : public std::enable_shared_from_this<cell> {
public:
    cell(std::unique_ptr<terrain> Terrain, Coords_t coords);

    cell(terrainType TerrainType, Coords_t coords);

    ~cell();

    char getCharForm();

    std::shared_ptr<character> getCharacter() const;

    std::shared_ptr<character> &&MoveCharacter();

    void setCharacter(std::shared_ptr<character> Char);

    Coords_t getCoords() const;

    bool isWalkable() const;

protected:
    std::unique_ptr<terrain> Terrain;
    std::shared_ptr<object> Object;
    std::shared_ptr<character> Character;
    Coords_t coords;
};
