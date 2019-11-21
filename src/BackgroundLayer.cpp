#include <SDL.h>
#include <string>
#include <memory>

#include "GraphicsLayer.h"
#include "Texture.h"
#include "BackgroundLayer.h"


BackgroundLayer::BackgroundLayer(const std::string path, SDL_Renderer* renderer) : GraphicsLayer(renderer) {
    background_ = std::make_unique<Texture>();
    background_->loadTexture(path, renderer);
}

void BackgroundLayer::render() {
    background_->render(renderer_);
}