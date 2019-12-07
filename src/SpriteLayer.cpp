#include <algorithm>

#include "GraphicsLayer.h"
#include "SpriteLayer.h"

SpriteLayer::SpriteLayer(SDL_Renderer* renderer) : GraphicsLayer(renderer) {}

void SpriteLayer::render() {
    std::for_each(sprites_.begin(), sprites_.end(), [this](auto s) {
        s->render(this->renderer_);
    });
}

void SpriteLayer::addSprite(Sprite* texture) {
    sprites_.emplace_back(texture);
}

void SpriteLayer::update(const int elapsedTime) {
    std::for_each(sprites_.begin(), sprites_.end(), [this, elapsedTime](auto s) {
        s->update(elapsedTime);
    });
}

void SpriteLayer::clearSprites() {
    sprites_.clear();
}