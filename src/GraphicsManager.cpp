
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>
#include <algorithm>

#include "GraphicsLayer.h"
#include "GraphicsManager.h"

GraphicsManager::GraphicsManager(int const screenWidth, int const screenHeight) {
    screenWidth_ = screenWidth;
    screenHeight_ = screenHeight;
}

GraphicsManager::~GraphicsManager() {
    close();
}

// need to manually clean up SDL using the provided methods.
void GraphicsManager::close() {
    SDL_DestroyWindow( window_ );
    SDL_DestroyRenderer(renderer_);

    IMG_Quit();
    SDL_Quit();
}

bool GraphicsManager::init() {
    std::cout << "Creating Main Window " << std::endl;

    // init SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        std::cout << "SDL Window could not be initialized! Error: " <<  SDL_GetError() << std::endl;
        return false;
    }

    // create the main window
    window_ = SDL_CreateWindow( "The Probe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->screenWidth_, this->screenHeight_, SDL_WINDOW_SHOWN );

    if (window_ == nullptr) {
        std::cout << "Could not create main window! Error: " <<  SDL_GetError() <<  std::endl;
        return false;
    }

    // initialize png loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
        std::cout << "Could not initialize image loading! Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer_ = SDL_CreateRenderer( window_, -1, SDL_RENDERER_ACCELERATED );

    if (renderer_ == nullptr) {
        std::cout << "Renderer could not be created! Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor( renderer_, 0xFF, 0xFF, 0xFF, 0xFF );

    return true;
}


void GraphicsManager::addLayer(GraphicsLayer* layer) {
    layers_.emplace_back(layer);
}

void GraphicsManager::render() {
    SDL_RenderClear( renderer_ );
    std::for_each(std::begin(layers_), std::end(layers_), [this](GraphicsLayer* l) { if(!l->isHidden) l->render(); });
    SDL_RenderPresent( renderer_ );
}

void GraphicsManager::clearLayers() {
    layers_.clear();
}

SDL_Renderer* GraphicsManager::getRenderer() {
    return renderer_;
}