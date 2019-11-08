#include <SDL.h>
#include <memory>
#include <string>
#include <iostream>

#include "SimpleBackgroundLayer.h"
#include "Texture.h"

SimpleBackgroundLayer::SimpleBackgroundLayer(std::string const path, SDL_Renderer* renderer) {
    background_ = std::unique_ptr<Texture>(new Texture()); 
    background_->loadTexture(path, renderer);
}

void SimpleBackgroundLayer::render(SDL_Renderer* renderer) {
    // render the background image
    SDL_RenderCopy( renderer, background_->getTexture(), NULL, NULL );
}