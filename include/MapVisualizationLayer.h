#ifndef MAPVISUALIZATIONLAYER
#define MAPVISUALIZATIONLAYER

#include <SDL.h>
#include <memory>

#include "WorldMap.h"
#include "Sprite.h"
#include "GraphicsLayer.h"

const std::string gMapTiles = "images/tilesetP8.png";

// map tile idx
const int gMapTile_grass = 0;
const int gMapTile_water = 1;
const int gMapTile_sand = 2;
const int gMapTile_mountain = 3;
const int gMapTile_tallMountain = 4;

// tile sizes
const int gMapTile_width = 8;
const int gMapTile_height = 8;

// tile positions
constexpr std::pair<const int, const int> gTilePosGrass = std::pair<const int, const int>(1, 0);
constexpr std::pair<const int, const int> gTilePosWater = std::pair<const int, const int>(1, 14);
constexpr std::pair<const int, const int> gTilePosSand = std::pair<const int, const int>(0, 19);
constexpr std::pair<const int, const int> gTilePosMountain = std::pair<const int, const int>(19, 4);
constexpr std::pair<const int, const int> gTilePosTallMountain = std::pair<const int, const int>(28, 0);

class MapVisualizationLayer final : public GraphicsLayer {
public:
    MapVisualizationLayer(SDL_Renderer* renderer, const std::string mapTilesSpriteSheet);
    void render() override;

    void setMap(WorldMap* map);

private:
    void addMapTile(const std::pair<const int, const int> position);
    void drawMapTile(const int tileX, const int tileY);

    WorldMap* map_; //non owning data handle.
    std::unique_ptr<Sprite> mapTiles_;
};

#endif