#ifndef MAPLAYER
#define MAPLAYER

#include <SDL.h>
#include <memory>

#include "IGraphicsLayer.h"
#include "Texture.h"
#include "WorldMap.h"

class MapLayer final : public IGraphicsLayer {
public:
    MapLayer(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer) override;

    void setWorldMap(WorldMap* map);

private:
    std::unique_ptr<Texture> waterTile_;
    std::unique_ptr<Texture> landTile_;
    std::unique_ptr<Texture> volcanoTile_;

    WorldMap* worldMap_;

};

#endif