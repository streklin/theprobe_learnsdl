#ifndef MAPTILE
#define MAPTILE

#include <vector>

#include "WorldMap.h"

class MapTileEmitter final {
public:
    MapTileEmitter(const int x, const int y, const int power);
    std::vector<std::vector<MapTile>> emitTiles();

private:
    int x_;
    int y_;
    int power_;
};

class MapFactory final {
public:
    MapFactory(const int width, const int height, const int iterations);
    WorldMap* generateNewWorld(const int seed);

private:
    int height_;
    int width_;
    int iterations_;
};

#endif