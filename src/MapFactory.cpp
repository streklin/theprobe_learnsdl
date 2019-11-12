#include <vector>
#include "MapFactory.h"

MapTileEmitter::MapTileEmitter(const int x, const int y, const int power) {}

std::vector<std::vector<MapTile>> MapTileEmitter::emitTiles() {
    std::vector<std::vector<MapTile>> v;
    return v;
}

MapFactory::MapFactory(const int width, const int height, const int iterations) {}

WorldMap* MapFactory::generateNewWorld(const int seed) {
    return nullptr;
}