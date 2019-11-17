#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include <utility>

#include "WorldMap.h"
#include "MapFactory.h"

#define MINTILEEMITTERS 16
#define MAXTILEEMITTERS 64

#define MINPOWER 16
#define MAXPOWER 64

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
            worldMap->setTileAt(wx, wy, MapTile::mDirt);
            break;
        case MapTile::mVolcano:
            break;     
        default:
            worldMap->setTileAt(wx, wy, MapTile::mDirt);
    }

}

void MapTileEmitter::emitTiles(WorldMap* world, MapTile l1, MapTile l2, MapTile l3) {
    std::random_device dev;
    std::mt19937 rng(dev());
    
    std::uniform_int_distribution<int> walkLengthDistribution(MINPOWER, MAXPOWER);
    std::uniform_int_distribution<int> directionDistribution(0, 4);

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

const int MapTileEmitter::x() { return x_; }
const int MapTileEmitter::y() { return y_; }
const int MapTileEmitter::power() { return power_; }

MapFactory::MapFactory() {}

MapFactory::MapFactory(const int width, const int height, const int iterations) {
    height_ = height;
    width_ = width;
    iterations_ = iterations;
    emitterFactory_ = MapTileEmitterFactory(width, height);
}


MapTileEmitterFactory::MapTileEmitterFactory() {}

MapTileEmitterFactory::MapTileEmitterFactory(const int width, const int height) {
    width_ = width;
    height_ = height;

    widthDistribution_ = std::uniform_int_distribution<int>(0, MAP_WIDTH);
    heightDistribution_ = std::uniform_int_distribution<int>(0, MAP_HEIGHT);
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

void MapFactory::generateContinents(WorldMap* worldMap) {
    std::random_device dev;
    std::mt19937 rng(dev());

    std::uniform_int_distribution<int> distribution(MINTILEEMITTERS, MAXTILEEMITTERS);
    const int numberOfEmitters = distribution(rng);

    std::vector<MapTileEmitter> emitters(numberOfEmitters);

    std::generate(emitters.begin(), emitters.end(), [this](){
        return this->emitterFactory_.getEmitter();
    });

    std::for_each(emitters.begin(), emitters.end(), [worldMap](MapTileEmitter &emitter){
        worldMap->setTileAt(emitter.x(), emitter.y(), MapTile::mVolcano);
    });
    
    std::uniform_int_distribution<int> emitterDistribution(0, numberOfEmitters);
    
    for(int i = 0; i < iterations_; i++) {
        const int index = emitterDistribution(rng);
        emitters[index].emitTiles(worldMap, MapTile::mDirt, MapTile::mHills, MapTile::mMountain);
    }
}

void MapFactory::generateFaultLines(WorldMap* worldMap) {
    // choose a potential fault line

    // do a random walk towards the water

    // increase the height of the map tiles along the random walk
    // to create hills and mountains
    
}

WorldMap* MapFactory::generateNewWorld(const int seed) {

    WorldMap* worldMap = new WorldMap();

    generateContinents(worldMap);
    generateFaultLines(worldMap);

    return worldMap;
}