#include <algorithm>

#include "GraphicsLayer.h"
#include "StaticTextureLayer.h"

StaticTextureLayer::StaticTextureLayer(SDL_Renderer* renderer) : GraphicsLayer(renderer) {}
    
void StaticTextureLayer::render() {
    std::for_each(textureList_.begin(), textureList_.end(), [this](Texture* t) {
        t->render(this->renderer_);
    });
}
    
void StaticTextureLayer::addTexture(Texture* texture) {
    textureList_.emplace_back(texture);
}