#ifndef SIMPLEBACKGROUNDLAYER
#define SIMPLEBACKGROUNDLAYER

#include <SDL.h>
#include <string>
#include <memory>

#include "Texture.h"
#include "IGraphicsLayer.h"

class SimpleBackgroundLayer final : public IGraphicsLayer {
public:
    SimpleBackgroundLayer(std::string const path, SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer) override;

private:
    std::unique_ptr<Texture> background_;
};

#endif