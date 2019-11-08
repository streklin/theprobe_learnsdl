#include <SDL.h>

#include <memory>
#include <iostream>

#include "stateIdList.h"
#include "AudioManager.h"
#include "IGraphicsLayer.h"
#include "SimpleBackgroundLayer.h"
#include "TitleScreenUXLayer.h"
#include "TitleScreenState.h"

TitleScreenState::TitleScreenState(GraphicsManager* manager, AudioManager* audioManager, int const stateId) : GameState(manager, audioManager, stateId) {
    backgroundLayer_ = std::shared_ptr<IGraphicsLayer>( static_cast<IGraphicsLayer*>(new SimpleBackgroundLayer("images/Space1.png", manager->renderer()) ) );
    uxLayer_ = std::shared_ptr<IGraphicsLayer>( static_cast<IGraphicsLayer*>( new TitleScreenUXLayer(manager->renderer()) ) );

    exitState_ = false;
}

void TitleScreenState::enterState() {
    graphicsManager_->clearLayers();

    audioManager_->loadMusicMedia("music/TitleMusic.ogg");
    audioManager_->play();
    graphicsManager_->addLayer(backgroundLayer_);
    graphicsManager_->addLayer(uxLayer_);
}

void TitleScreenState::exitState() {
    audioManager_->stop();
}

bool TitleScreenState::handleEvents(SDL_Event* e) {
    int x, y;
    SDL_GetMouseState( &x, &y );

    if( e->type == SDL_MOUSEMOTION ) {
        uxLayer_->updateMouse(x,  y);
    }

    if ( e->type == SDL_MOUSEBUTTONDOWN) {
        exitState_ = true;
    }

    return true;
}

int TitleScreenState::gameLoop(int const elapsedTime) {
    if (exitState_) return worldGeneratorStateId;
    return -1;
}