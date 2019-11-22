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
    buildButtonLayer();
}

void TitleScreenState::exitState() {}

void TitleScreenState::update(int elapsedTicks) {
    if (startGameBtn_->isClicked()) {
        std::cout << "Start the game \n";
    }

    if (exitGameBtn_->isClicked()) {
        std::cout << "end the game \n";
    }
} 

States TitleScreenState::nextState() {
    return States::TitleScreen;
}

bool TitleScreenState::isReadyToTransition() {
    return false;
}

void TitleScreenState::handleEvents(SDL_Event* e) {
    buttonLayer_->handleEvents(e);
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

void TitleScreenState::buildButtonLayer() {
    startGameBtn_ = std::make_unique<Button>("images/Button.png", graphics_->getRenderer(), 65, 103);
    startGameBtn_->setPosition(840, 140);

    exitGameBtn_ = std::make_unique<Button>("images/Button.png", graphics_->getRenderer(), 65, 103);
    exitGameBtn_->setPosition(840, 220);

    buttonLayer_ = std::make_unique<ButtonLayer>(graphics_->getRenderer());
    buttonLayer_->addButton(startGameBtn_.get());
    buttonLayer_->addButton(exitGameBtn_.get());

    graphics_->addLayer(static_cast<GraphicsLayer*>(buttonLayer_.get()));
}