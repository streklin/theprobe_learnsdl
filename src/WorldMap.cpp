#include <vector>
#include <array>

#include "WorldMap.h"

WorldMap::WorldMap() {}

MapTile WorldMap::getTileAt(const int x, const int y) {
    return MapTile::mDirt;
}

void WorldMap::updateTiles(const int cx, const int cy, const std::vector<std::vector<MapTile>> emittedTiles) {}

