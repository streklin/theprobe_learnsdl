
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>

#include "Texture.h"

Texture::Texture() {
    xScale_ = 1;
    yScale_ = 1;
    x_ = 0;
    y_ = 0;
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
    SDL_Rect source = {0, 0, width_, height_};
    SDL_Rect target = {x_, y_, width_ * xScale_, height_ * yScale_};
    SDL_RenderCopy( renderer, texture_, &source, &target );
}

void Texture::setScale(const float x, const float y) {
    xScale_ = x;
    yScale_ = y;
}

void Texture::setPosition(const int x, const int y) {
    x_ = x;
    y_ = y;
}
