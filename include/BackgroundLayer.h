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
    void render() override;

private:
    std::unique_ptr<Texture> background_;
};

#endif