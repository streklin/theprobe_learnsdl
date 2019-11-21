#include <SDL.h>
#include "GraphicsLayer.h"

GraphicsLayer::GraphicsLayer(SDL_Renderer* renderer) {
    renderer_ = renderer; 
    isHidden = false; 
}

void GraphicsLayer::render() {}

void GraphicsLayer::updateMouse(int const x, int const y) {}
