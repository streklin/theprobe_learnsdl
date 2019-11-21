#include "GameState.h"

GameState::GameState() {
    isReadyToTransition_ = false;
}

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

States GameState::nextState() { return States::TitleScreen; }

bool GameState::isReadyToTransition() { return isReadyToTransition_; }

void GameState::handleEvents(SDL_Event* e) {}