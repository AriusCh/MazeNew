#pragma once

#include <memory>

class Terrain;
class Object;
class Character;
class Dungeon;

enum class terrainType;

struct Coords_t {
    int y;
    int x;
};

class Cell : public std::enable_shared_from_this<Cell> {
public:
    Cell(std::unique_ptr<Terrain> terrain, Coords_t coords);

    Cell(terrainType TerrainType, Coords_t coords);

    ~Cell();

    char getCharForm();

    std::shared_ptr<Character> getCharacter() const;

    std::shared_ptr<Character> &&moveCharacter();

    void setCharacter(std::shared_ptr<Character> newChar);

    Coords_t getCoords() const;

    bool isWalkable() const;

protected:
    std::unique_ptr<Terrain> terrain;
    std::shared_ptr<Object> object;
    std::shared_ptr<Character> character;
    Coords_t coords;
};
