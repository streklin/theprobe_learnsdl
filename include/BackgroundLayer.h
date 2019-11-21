#ifndef BACKGROUNDLAYER
#define BACKGROUNDLAYER

#include <SDL.h>
#include <string>
#include <memory>

#include "GraphicsLayer.h"
#include "Texture.h"

class BackgroundLayer final : public GraphicsLayer {
public:
    BackgroundLayer(const std::string path, SDL_Renderer* renderer);
    virtual void render();

private:
    std::unique_ptr<Texture> background_;
};

#endif