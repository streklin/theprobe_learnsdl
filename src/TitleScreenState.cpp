#include "TitleScreenState.h"
#include "BackgroundLayer.h"
#include "GameState.h"

TitleScreenState::TitleScreenState(GraphicsManager* graphics, AudioManager* audio) : GameState(graphics, audio) {
}

void TitleScreenState::enterState() {
}

void TitleScreenState::exitState() {
}

void TitleScreenState::update(int elapsedTicks) {} 

States TitleScreenState::nextState() {
    return States::TitleScreen;
}

bool TitleScreenState::isReadyToTransition() {
    return false;
}