#include "GameState.h"

GameState::GameState(GraphicsManager* graphics, AudioManager* audio) {
    graphics_ = graphics;
    audio_ = audio;
    isReadyToTransition_ = false;
}

GameState::~GameState() {
    exitState();
}

void GameState::enterState() {}

void GameState::exitState() {}

void GameState::update(int elapsedTicks){} 

GameState* GameState::nextState() { return nullptr; }

bool GameState::isReadyToTransition() { return isReadyToTransition_; }