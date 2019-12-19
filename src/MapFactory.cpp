#include <memory>
#include <mutex>
#include <algorithm>
#include <iostream>
#include "MapFactory.h"
#include "WorldMap.h"

#define MINTILEEMITTERS 16
#define MAXTILEEMITTERS 32

#define MINPOWER 16
#define MAXPOWER 64

#define MAXFORESTS 50
#define MAXSAMPLES 1000
#define FORESTPOWER 32

#define MAXCITIES 20
#define MINCITIES 5

#define MAPGENERATIONITERATIONS 2500

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

MapTileEmitter::MapTileEmitter() {}

MapTileEmitter::MapTileEmitter(const int x, const int y, const int power) {
    x_ = x;
    y_ = y;
    power_ = power;
}

std::pair<const int,const int> MapTileEmitter::getNextMapLocation(WorldMap* worldMap, const int direction, const int wx, const int wy) {

    if (wx < 0 || wy < 0) {
        throw "Bad Position";
    }

    if (wx >= MAP_WIDTH || wy >= MAP_HEIGHT) {
        throw "Bad Position";
    }

    int nextX = 0;
    int nextY = 0;
  
    switch(direction) {
        case UP: 
            nextX = wx;
            nextY = wy - 1;
            break;
        case LEFT: 
            nextY = wy;
            nextX = wx - 1;
        break;
        case DOWN: 
            nextX = wx;
            nextY = wy + 1;
        break;
        case RIGHT: 
            nextY = wy;
            nextX = wx + 1;
        break;
    }

    if (nextX < 0) nextX = 0;
    if (nextY < 0) nextY = 0;

    if (nextX > MAP_WIDTH - 1) nextX = MAP_WIDTH -1;
    if (nextY > MAP_HEIGHT - 1) nextY = MAP_HEIGHT -1;

  
    return std::pair(nextX, nextY);    
}


void MapTileEmitter::emitTiles(WorldMap* world, MapTile tile) {
    std::random_device dev;
    std::mt19937 rng(dev());
    
    std::uniform_int_distribution<int> walkLengthDistribution(MINPOWER, MAXPOWER);
    std::uniform_int_distribution<int> directionDistribution(0, 3);

    const int walkLength = walkLengthDistribution(rng);
    int wx = x_;
    int wy = y_;

    for (int i = 0; i < walkLength; i++) {
        const int direction = directionDistribution(rng);
        auto nextPosition = getNextMapLocation(world, direction, wx, wy);
        world->setTileAt(nextPosition.first, nextPosition.second, tile);

        wx = nextPosition.first;
        wy = nextPosition.second;
    }

}

void MapTileEmitter::randomWalkToWater(WorldMap* worldMap) {
    std::random_device dev;
    std::mt19937 rng(dev());

    std::uniform_int_distribution<int> directionDistribution(0, 3);
    int wx = x_;
    int wy = y_;

    int maxLength = 50;
    
    while(maxLength > 0) {
    
        worldMap->setTileAt(wx, wy, MapTile::mMountain);
        const int direction = directionDistribution(rng);
        auto nextPosition = getNextMapLocation(worldMap, direction, wx, wy);
        
        wx = nextPosition.first;
        wy = nextPosition.second;

        maxLength--;
    }
    
}

const int MapTileEmitter::x() { return x_; }
const int MapTileEmitter::y() { return y_; }
const int MapTileEmitter::power() { return power_; }


MapTileEmitterFactory::MapTileEmitterFactory() {
    widthDistribution_ = std::uniform_int_distribution<int>(0, MAP_WIDTH - 1);
    heightDistribution_ = std::uniform_int_distribution<int>(0, MAP_HEIGHT - 1);
    powerDistribution_ = std::uniform_int_distribution<int>(MINPOWER, MAXPOWER);
}

MapTileEmitter MapTileEmitterFactory::getEmitter() {

    std::random_device dev;
    std::mt19937 rng(dev());

    const int x = widthDistribution_(rng);
    const int y = heightDistribution_(rng);
    const int power = powerDistribution_(rng);

    return MapTileEmitter(x, y, power);
}


MapFactory::MapFactory() {
    isWorldReady_ = true;
}


void MapFactory::generateEmitters(WorldMap* worldMap_) {
    std::random_device dev;
    std::mt19937 rng(dev());

    std::uniform_int_distribution<int> distribution(MINTILEEMITTERS, MAXTILEEMITTERS);
    const int numberOfEmitters = distribution(rng);

    tileEmitters_ = std::vector<MapTileEmitter>(numberOfEmitters);

    MapTileEmitterFactory emitterFactory;
    std::generate(tileEmitters_.begin(), tileEmitters_.end(), [&emitterFactory](){
        return emitterFactory.getEmitter();
    });
}

void MapFactory::generateContinents(WorldMap* worldMap_) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> emitterDistribution(0, tileEmitters_.size() - 1);
    
    for(int i = 0; i < MAPGENERATIONITERATIONS; i++) {
        const int index = emitterDistribution(rng);
        tileEmitters_[index].emitTiles(worldMap_, MapTile::mGrass);
    }
}

void MapFactory::generateMountains(WorldMap* worldMap_) {
    std::for_each(tileEmitters_.begin(), tileEmitters_.end(), [worldMap_](auto emitter) {
        emitter.randomWalkToWater(worldMap_);
    });

}

bool MapFactory::isAdjancentToType(const int x, const int y, const MapTile tile, WorldMap* worldMap_) {
    if (worldMap_->isTileAt(x - 1, y, tile)) return true;
    if (worldMap_->isTileAt(x + 1, y, tile)) return true;
    if (worldMap_->isTileAt(x, y + 1, tile)) return true;
    if (worldMap_->isTileAt(x, y - 1, tile)) return true;

    return false;
}

void MapFactory::generateShorelines(WorldMap* worldMap_) {
    for (int x = 0; x < MAP_WIDTH; x++) {
        for (int y = 0; y < MAP_HEIGHT; y++) {
            if (worldMap_->getTileAt(x, y) != MapTile::mGrass) continue;
            if (isAdjancentToType(x, y, MapTile::mWater, worldMap_)) worldMap_->setTileAt(x, y, MapTile::mDesert);
        }
    }
}

void MapFactory::generateHills(WorldMap* worldMap_) {}

std::pair<const int, const int> MapFactory::sampleForTile(MapTile tile, WorldMap* worldMap) {
 
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> widthDistribution = std::uniform_int_distribution<int>(0, MAP_WIDTH - 1);
    std::uniform_int_distribution<int> heightDistribution = std::uniform_int_distribution<int>(0, MAP_HEIGHT - 1);

    int sampleCount = 0;

    while(sampleCount < MAXSAMPLES) {
        sampleCount++;

        const int x = widthDistribution(rng);       
        const int y = heightDistribution(rng);

        if (worldMap->getTileAt(x,y) == tile) return std::pair<const int, const int>(x, y);
    }

    return std::pair<const int, const int>(-1, -1);
}

void MapFactory::generateForests(WorldMap* worldMap_) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> forestCountDist(0, MAXFORESTS);

    const int numberOfForests = forestCountDist(rng);

    for (int i = 0; i < numberOfForests; i++) {
        auto nextTile = sampleForTile(MapTile::mGrass, worldMap_);

        if (nextTile.first == -1) continue;

        auto emitter = MapTileEmitter(nextTile.first, nextTile.second, FORESTPOWER);
        emitter.emitTiles(worldMap_, MapTile::mForest);
    }
}

void MapFactory::generateArcticBiome(WorldMap* worldMap_) {}


void MapFactory::generateWorld(WorldMap* worldMap) {
    isWorldReady_ = false;

    worldMap->clearMap();

    generateEmitters(worldMap);
    generateContinents(worldMap);
    generateShorelines(worldMap);
    generateMountains(worldMap);

    generateHills(worldMap);
    generateForests(worldMap);
    generateArcticBiome(worldMap);

    isWorldReady_ = true;
}

bool MapFactory::isReady() { 
    std::lock_guard<std::mutex> myLock(mutex_);
    return isWorldReady_;
}



