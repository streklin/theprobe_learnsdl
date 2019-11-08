#include <SDL.h>
#include <memory>

#include "stateIdList.h"
#include "AudioManager.h"
#include "SimpleBackgroundLayer.h"
#include "GameState.h"
#include "IGraphicsLayer.h"
#include "WorldGeneratorState.h"


WorldGeneratorState::WorldGeneratorState(GraphicsManager* manager, AudioManager* audioManager, int const stateId) : GameState(manager, audioManager, stateId) {
    backgroundLayer_ = std::shared_ptr<IGraphicsLayer>(static_cast<IGraphicsLayer*>(new SimpleBackgroundLayer("images/Space2.png", manager->renderer())));
}

void WorldGeneratorState::enterState() {
    graphicsManager_->clearLayers();
    graphicsManager_->addLayer(backgroundLayer_);
}

void WorldGeneratorState::exitState() {}


int WorldGeneratorState::gameLoop(int const elapsedTime) {
    return -1;
}

bool WorldGeneratorState::handleEvents(SDL_Event* e) {
    return true;
}