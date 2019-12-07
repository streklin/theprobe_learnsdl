#ifndef MAPFACTORY
#define MAPFACTORY

#include <utility>
#include <random>
#include <vector>
#include <memory>
#include <mutex>
#include <array>
#include "WorldMap.h"


const int gConvolutionWidth = 3;
const int gConvolutionHeight = 3;

class MapTileEmitter final {
public:
    MapTileEmitter();
    MapTileEmitter(const int x, const int y, const int power);
    void emitTiles(WorldMap* worldMap, MapTile tile);
    void randomWalkToWater(WorldMap* worldMap);

    const int x();
    const int y();
    const int power();

private:
    std::pair<const int,const int> getNextMapLocation(WorldMap* worldMap, const int direction, const int wx, const int wy);
    
    int x_;
    int y_;
    int power_;
};

class MapTileEmitterFactory final {
public:
    MapTileEmitterFactory();
    MapTileEmitter getEmitter();
private:
    std::uniform_int_distribution<int> widthDistribution_;
    std::uniform_int_distribution<int> heightDistribution_;
    std::uniform_int_distribution<int> powerDistribution_;
};

class MapFactory final {
public:
    MapFactory();
    void generateWorld(WorldMap* map);
    bool isCompleted();

private:

    void generateEmitters(WorldMap* worldMap_);
    void generateContinents(WorldMap* worldMap_);
    void generateMountains(WorldMap* worldMap_);
    void generateShorelines(WorldMap* worldMap_);
    void generateHills(WorldMap* worldMap_);
    void generateForests(WorldMap* worldMap_);
    void generateArcticBiome(WorldMap* worldMap_);
    void generateCities(WorldMap* worldMap_);
    void connectCities(WorldMap* worldMap_);

    std::pair<const int, const int> sampleForTile(MapTile tile, WorldMap* worldMap);

    bool isAdjancentToType(const int x, const int y, const MapTile tile, WorldMap* worldMap_);
    
    std::vector<MapTileEmitter> tileEmitters_;
    std::mutex mutex_;
    bool isWorldReady_;

};

#endif