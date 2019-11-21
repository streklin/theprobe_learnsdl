#ifndef STATICTEXTURELAYER
#define STATICTEXTURELAYER

#include <SDL.h>
#include <SDL_image.h>

#include <vector>

#include "Texture.h"
#include "GraphicsLayer.h"

class StaticTextureLayer final : public GraphicsLayer {
public:
    StaticTextureLayer(SDL_Renderer* renderer);
    
    void render() override;
    
    void addTexture(Texture* texture);

private:
    std::vector<Texture*> textureList_;
};

#endif