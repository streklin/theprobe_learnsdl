#ifndef MAPTILE
#define MAPTILE

#include <utility>
#include <random>
#include <vector>

#include "WorldMap.h"

class MapTileEmitter final {
public:
    MapTileEmitter();
    MapTileEmitter(const int x, const int y, const int power);
    void emitTiles(WorldMap* worldMap, MapTile l1, MapTile l2, MapTile l3);
    void randomWalkToWater(WorldMap* worldMap);

    const int x();
    const int y();
    const int power();

private:
    std::pair<const int,const int> getNextMapLocation(WorldMap* worldMap, const int direction, const int wx, const int wy);
    void setTileAtLocation(WorldMap* worldMap, const int wx, const int wy);

    int x_;
    int y_;
    int power_;
};

class MapTileEmitterFactory final {
public:
    MapTileEmitterFactory();
    MapTileEmitterFactory(const int width, const int height);
    MapTileEmitter getEmitter();
private:
    std::uniform_int_distribution<int> widthDistribution_;
    std::uniform_int_distribution<int> heightDistribution_;
    std::uniform_int_distribution<int> powerDistribution_;

    int width_;
    int height_;
};

class MapFactory final {
public:
    MapFactory();
    MapFactory(const int width, const int height, const int iterations);
    WorldMap* generateNewWorld(const int seed);

private:
    void generateContinents(WorldMap* worldMap);
    void generateFaultLines(WorldMap* worldMap);

    int height_;
    int width_;
    int iterations_;

    MapTileEmitterFactory emitterFactory_;
};

#endif