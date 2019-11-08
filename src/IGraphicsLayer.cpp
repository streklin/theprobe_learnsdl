#include "IGraphicsLayer.h"

IGraphicsLayer::IGraphicsLayer() { isHidden = false; }
void IGraphicsLayer::render(SDL_Renderer* renderer) {}
void IGraphicsLayer::updateMouse(int const x, int const y) {}