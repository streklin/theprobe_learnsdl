#include "GameState.h"
#include "GraphicsManager.h"
#include "AudioManager.h"

GameState::GameState(GraphicsManager* manager, AudioManager* audioManager, int const stateId) {
    graphicsManager_ = manager;
    audioManager_ = audioManager;
    stateId_ = stateId;
}

void GameState::enterState() {}

void GameState::exitState() {}

int GameState::gameLoop(int const elapsedTime) {
    return 0;
}

int GameState::stateId() { return stateId_; }

bool GameState::handleEvents(SDL_Event* e) { return true; }