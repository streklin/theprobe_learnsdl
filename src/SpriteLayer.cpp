#include <memory>
#include <algorithm>
#include <iostream>
#include "SpriteLayer.h"

SpriteLayer::SpriteLayer() {}

void SpriteLayer::addSprite(std::shared_ptr<Sprite> sprite) {
    sprites_.emplace_back(sprite);
}

void SpriteLayer::render(SDL_Renderer* renderer) {
    std::for_each(std::begin(sprites_), std::end(sprites_), 
        [renderer](std::shared_ptr<Sprite> s) {
            s->update();
            s->render(renderer);
        });
}

void SpriteLayer::updateMouse(int const x, int const y) {}

void SpriteLayer::clearSprites() {
    sprites_.clear();
}