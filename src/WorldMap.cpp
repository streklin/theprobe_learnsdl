#include <vector>
#include <array>
#include <iostream>

#include "WorldMap.h"

WorldMap::WorldMap() {
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            map_[x][y] = MapTile::mWater;
        }
    }

}

MapTile WorldMap::getTileAt(const int x, const int y) {
    return map_[x][y];
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