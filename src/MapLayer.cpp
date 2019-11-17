#include <SDL.h>
#include <memory>

#include "IGraphicsLayer.h"
#include "Texture.h"
#include "WorldMap.h"
#include "MapLayer.h"

#define GROUNDTILE "images/land.png"
#define WATERTILE "images/water.png"
#define VOLCANOTILE "images/volcanoe.png"

MapLayer::MapLayer(SDL_Renderer* renderer) {
    isHidden = true;

    waterTile_ = std::unique_ptr<Texture>(new Texture());
    waterTile_->loadTexture(WATERTILE, renderer);

    landTile_ = std::unique_ptr<Texture>(new Texture());
    landTile_->loadTexture(GROUNDTILE, renderer);

    volcanoTile_ = std::unique_ptr<Texture>(new Texture());
    volcanoTile_->loadTexture(VOLCANOTILE, renderer);
}

void MapLayer::render(SDL_Renderer* renderer) {

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            auto tile = worldMap_->getTileAt(x, y);

            SDL_Rect source = {0, 0, 256, 256};
            SDL_Rect target = {x * 16, y * 16, 16, 16};

            switch(tile) {
                case MapTile::mDirt:
                    SDL_RenderCopy(renderer, landTile_->getTexture(), &source, &target);
                    break;
                case MapTile::mWater:
                    SDL_RenderCopy(renderer, waterTile_->getTexture(), &source, &target);
                    break;
                case MapTile::mVolcano:
                    SDL_RenderCopy(renderer, volcanoTile_->getTexture(), &source, &target);
                    break; 
                default:
                    SDL_RenderCopy(renderer, landTile_->getTexture(), &source, &target);
                    break;
            }
        }
    }
}

void MapLayer::setWorldMap(WorldMap* map) {
    worldMap_ = map;
}