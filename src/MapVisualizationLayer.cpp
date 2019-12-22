#include <SDL.h>
#include <memory>
#include <iostream>

#include "WorldMap.h"
#include "Sprite.h"
#include "GraphicsLayer.h"
#include "MapVisualizationLayer.h"
#include "Animation.h"

MapVisualizationLayer::MapVisualizationLayer(SDL_Renderer* renderer, const std::string mapTilesSpriteSheet) : GraphicsLayer(renderer) {
    mapTiles_ = std::make_unique<Sprite>(mapTilesSpriteSheet, renderer);
    mapTiles_->setScale(1.0, 1.0);

    map_offset_x_ = 0;
    map_offset_y_ = 0;
    zoom_level_ = 1.0f;

    addMapTile(gTilePosGrass);
    addMapTile(gTilePosWater);
    addMapTile(gTilePosSand);
    addMapTile(gTilePosMountain);
    addMapTile(gTilePosTallMountain);
    addMapTile(gTilePosTrees);
    addMapTile(gTilePosCity);
}

void MapVisualizationLayer::setMapOffset(const int map_offset_x, const int map_offset_y) {
    map_offset_x_ = map_offset_x;
    map_offset_y_ = map_offset_y;
}

void MapVisualizationLayer::setZoomLevel(const float zoom_level) {
    zoom_level_ = zoom_level;
    mapTiles_->setScale(zoom_level_, zoom_level_);
}

void MapVisualizationLayer::render() {
    for(int x = 0; x < MAP_WIDTH; x++) {
        for(int y = 0; y < MAP_HEIGHT; y++) {
            drawMapTile(x, y);
        }
    }
}

void MapVisualizationLayer::setMap(WorldMap* map) {
    map_ = map;
}

void MapVisualizationLayer::addMapTile(const std::pair<const int, const int> position) {
    const int frameXPos = position.first * gMapTile_width;
    const int frameYPos = position.second * gMapTile_height;

    Animation tileFrame = Animation(0);
    tileFrame.addFrame({frameXPos, frameYPos, gMapTile_width, gMapTile_height});

    mapTiles_->addAnimation(std::move(tileFrame));
}

void MapVisualizationLayer::drawMapTile(const int tileX, const int tileY) {
    switch(map_->getTileAt(tileX, tileY)) {
     
        case MapTile::mGrass: 
            mapTiles_->setAnimation(gMapTile_grass);
            break;
        case MapTile::mMountain: 
            mapTiles_->setAnimation(gMapTile_mountain);
            break;
        case MapTile::mWater: 
            mapTiles_->setAnimation(gMapTile_water);
            break;
        case MapTile::mDesert:
            mapTiles_->setAnimation(gMapTile_sand);
            break;
        case MapTile::mVolcano:
            mapTiles_->setAnimation(gMapTile_tallMountain);
            break;
        case MapTile::mForest:
            mapTiles_->setAnimation(gMapTile_forest);
            break;
        case MapTile::mCity:
            mapTiles_->setAnimation(gMapTile_city);
            break;
        default:
            mapTiles_->setAnimation(gMapTile_sand);
    }

    const int tile_x_position = (tileX * gMapTile_width * zoom_level_) + map_offset_x_;
    const int tile_y_position = (tileY * gMapTile_height * zoom_level_) + map_offset_y_;
    mapTiles_->renderAt(this->renderer_, tile_x_position, tile_y_position);
}