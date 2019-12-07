#include <memory>
#include <mutex>
#include <algorithm>
#include <iostream>
#include "MapFactory.h"
#include "WorldMap.h"

#define MINTILEEMITTERS 2
#define MAXTILEEMITTERS 8

#define MINPOWER 16
#define MAXPOWER 64

#define MAPGENERATIONITERATIONS 1000

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

MapTileEmitter::MapTileEmitter() {}

MapTileEmitter::MapTileEmitter(const int x, const int y, const int power) {
    x_ = x;
    y_ = y;
    power_ = power;

    std::cout << "X: " << x << ", Y: " << y << "\n";

}

std::pair<const int,const int> MapTileEmitter::getNextMapLocation(WorldMap* worldMap, const int direction, const int wx, const int wy) {

    if (wx < 0 || wy < 0) {
        throw "Bad Position";
    }

    if (wx >= MAP_WIDTH || wy >= MAP_HEIGHT) {
        throw "Bad Position";
    }

    std::cout << "Direction: " << direction << "\n";

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

void MapTileEmitter::setTileAtLocation(WorldMap* worldMap, const int wx, const int wy) { 
    auto tileAt = worldMap->getTileAt(wx, wy);
    
    switch(tileAt) {
        case MapTile::mWater:
            worldMap->setTileAt(wx, wy, MapTile::mGrass);
            break;
        case MapTile::mVolcano:
            break;     
        default:
            worldMap->setTileAt(wx, wy, MapTile::mGrass);
    }

}

void MapTileEmitter::emitTiles(WorldMap* world, MapTile l1, MapTile l2, MapTile l3) {
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
        setTileAtLocation(world, nextPosition.first, nextPosition.second);

        wx = nextPosition.first;
        wy = nextPosition.second;
    }

}

void MapTileEmitter::randomWalkToWater(WorldMap* worldMap) {
    // increase the height of the map tiles along the random walk
    // to create hills and mountains
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


MapFactory::MapFactory() {}


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
        tileEmitters_[index].emitTiles(worldMap_, MapTile::mGrass, MapTile::mHills, MapTile::mMountain);
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

void MapFactory::generateForests(WorldMap* worldMap_) {}

void MapFactory::generateArcticBiome(WorldMap* worldMap_) {}

void MapFactory::generateCities(WorldMap* worldMap_) {}

void MapFactory::connectCities(WorldMap* worldMap_) {}

void MapFactory::generateWorld(WorldMap* worldMap) {
    worldMap->clearMap();

    generateEmitters(worldMap);
    generateContinents(worldMap);
    generateShorelines(worldMap);
    generateMountains(worldMap);

    generateHills(worldMap);
    generateForests(worldMap);
    generateArcticBiome(worldMap);
    generateCities(worldMap);
    connectCities(worldMap);

    std::lock_guard<std::mutex> myLock(mutex_);
    isWorldReady_ = true;
}

bool MapFactory::isCompleted() { 
    std::lock_guard<std::mutex> myLock(mutex_);
    return isWorldReady_;
}



