#include <vector>
#include <array>
#include <iostream>
#include <random>

#include "WorldMap.h"

WorldMap::WorldMap() {
    clearMap();
}

MapTile WorldMap::getTileAt(const int x, const int y) {
    if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT) return MapTile::mWater;
    return map_[x][y];
}

bool WorldMap::isTileAt(const int x, const int y, const MapTile tile) {
    return getTileAt(x, y) == tile;
}

void WorldMap::setTileAt(const int x, const int y, const MapTile tile) {
    map_[x][y] = tile;
}

void WorldMap::outputTileToConsole(MapTile tile) {
        switch(tile) {
            case MapTile::mWater:
                std::cout << "."; 
                break;
            case MapTile::mDirt:
                std::cout << "#";
                break;
            case MapTile::mHills:
                std::cout << "^";
                break;
            case MapTile::mMountain:
                std::cout << "M";
                break;
            case MapTile::mVolcano:
                std::cout << "V";
            default:
                std::cout << ".";
        }
}

void WorldMap::outputMapToConsole() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            outputTileToConsole(map_[x][y]);
        }
        std::cout << "\n";
    }
}

void WorldMap::clearMap() {
   for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map_[x][y] = MapTile::mWater;
        }
    }
}

std::pair<const int, const int> WorldMap::sampleForTile(MapTile tile) {
 
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> widthDistribution = std::uniform_int_distribution<int>(0, MAP_WIDTH - 1);
    std::uniform_int_distribution<int> heightDistribution = std::uniform_int_distribution<int>(0, MAP_HEIGHT - 1);

    int sampleCount = 0;

    while(sampleCount < MAXSAMPLES) {
        sampleCount++;

        const int x = widthDistribution(rng);       
        const int y = heightDistribution(rng);

        if (this->getTileAt(x,y) == tile) return std::pair<const int, const int>(x, y);
    }

    return std::pair<const int, const int>(-1, -1);
}