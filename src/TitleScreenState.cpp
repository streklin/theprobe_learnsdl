#include <iostream>

#include "Texture.h"
#include "GraphicsLayer.h"
#include "TitleScreenState.h"
#include "BackgroundLayer.h"
#include "GameState.h"

TitleScreenState::TitleScreenState(GraphicsManager* graphics, AudioManager* audio) : GameState(graphics, audio) {
}

void TitleScreenState::enterState() {
    buildBackgroundLayer();
    buildStaticTextureLayer();
}

void TitleScreenState::exitState() {}

void TitleScreenState::update(int elapsedTicks) {} 

States TitleScreenState::nextState() {
    return States::TitleScreen;
}

bool TitleScreenState::isReadyToTransition() {
    return false;
}

void TitleScreenState::buildBackgroundLayer() {
    backgroundLayer_ = std::make_unique<BackgroundLayer>(titleScreenBackground, graphics_->getRenderer());
    graphics_->addLayer(static_cast<GraphicsLayer*>(backgroundLayer_.get()));
}

void TitleScreenState::buildStaticTextureLayer() {
    staticTextureLayer_ = std::make_unique<StaticTextureLayer>(graphics_->getRenderer());
    
    hudTexture_ = std::make_unique<Texture>();
    hudTexture_->loadTexture(hudTexture, graphics_->getRenderer());
    hudTexture_->setPosition(750, 50);
    hudTexture_->setScale(0.5, 1.0);
    
    staticTextureLayer_->addTexture(hudTexture_.get());
    
    graphics_->addLayer(static_cast<GraphicsLayer*>(staticTextureLayer_.get()));
} 