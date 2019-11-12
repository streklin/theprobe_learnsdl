#ifndef WORLDMAP
#define WORLDMAP

#define MAP_WIDTH 2048
#define MAP_HEIGHT 2048

#include <vector>
#include <array>

enum class MapTile {
    mDirt,
    mForest,
    mSnow,
    mGrass,
    mDesert,
    mWater,
    mTundra,
    mFarmland,
    mRoad,
    mMountain,
    mMarsh,
    mHills
};

class WorldMap final {
public:
    WorldMap();

    MapTile getTileAt(const int x, const int y);
    void updateTiles(const int cx, const int cy, const std::vector<std::vector<MapTile>> emittedTiles);

private:
    std::array<std::array<MapTile, MAP_HEIGHT>, MAP_WIDTH> map_;
};

#endif