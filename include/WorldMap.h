#ifndef WORLDMAP
#define WORLDMAP

#define MAP_WIDTH 150
#define MAP_HEIGHT 110

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
    mHills,
    mVolcano,
    mCity
};

class WorldMap final {
public:
    WorldMap();

    MapTile getTileAt(const int x, const int y);
    void setTileAt(const int x, const int y, const MapTile tile);
    bool isTileAt(const int x, const int y, const MapTile tile);
    
    void outputMapToConsole();
    void clearMap();

private:
    void outputTileToConsole(MapTile tile);

    std::array<std::array<MapTile, MAP_HEIGHT>, MAP_WIDTH> map_;
};

#endif