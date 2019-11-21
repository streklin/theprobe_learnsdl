
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

#include "Texture.h"

Texture::Texture() {
    xScale_ = 1;
    yScale_ = 1;
    texture_ = nullptr;
}

Texture::~Texture() {
    SDL_DestroyTexture(texture_);
}

bool Texture::loadTexture(const std::string path, SDL_Renderer* renderer) {

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());

    if (loadedSurface == nullptr) {
        std::cout << "Unable to load texture! Error: " << SDL_GetError() << std::endl;
        return false;
    }

    texture_ = SDL_CreateTextureFromSurface( renderer, loadedSurface );

    if (texture_ == nullptr) {
        std::cout << "Unable to create a texture! Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface( loadedSurface );
        return false;
    }

    width_ = loadedSurface->w;
    height_ = loadedSurface->h;

    SDL_FreeSurface( loadedSurface );
    
    return true;
}

SDL_Texture* Texture::getTexture() { return texture_; }

int Texture::getWidth() { return width_; }

int Texture::getHeight() { return height_; }

void Texture::render(SDL_Renderer* renderer) {
    SDL_RenderCopy( renderer, texture_, NULL, NULL );
}

void Texture::setScale(const float x, const float y) {
    xScale_ = x;
    yScale_ = y;
}
