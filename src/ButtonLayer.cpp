#include <SDL.h>

#include <vector>
#include <algorithm>

#include "Button.h"
#include "GraphicsLayer.h"
#include "ButtonLayer.h"


ButtonLayer::ButtonLayer(SDL_Renderer* renderer) : GraphicsLayer(renderer) {}

void ButtonLayer::render() {
    std::for_each(buttons_.begin(), buttons_.end(), [this](auto button) {
        button->render(this->renderer_);
    });
}

void ButtonLayer::handleEvents(SDL_Event* e) {
    std::for_each(buttons_.begin(), buttons_.end(), [e](auto button) {
        button->handleEvents(e);
    });
}

void ButtonLayer::addButton(Button* button) {
    buttons_.emplace_back(button);
}