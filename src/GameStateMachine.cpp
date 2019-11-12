#include <map>
#include <memory>
#include <string_view>
#include <iostream>

#include "stateIdList.h"

#include "GameStateMachine.h"
#include "AudioManager.h"
#include "TitleScreenState.h"
#include "WorldGeneratorState.h"

GameStateMachine::GameStateMachine() {

    currentState_ = nullptr;
    isGameExitTriggered_ = false;

    initializeManagerObjects();

    transition(titleScreenStateId);
}

void GameStateMachine::initializeManagerObjects() {
    graphicsManager_ = std::unique_ptr<GraphicsManager>(new GraphicsManager(1280, 960));
    audioManager_ = std::make_unique<AudioManager>(AudioManager());
    graphicsManager_->init();
}

void GameStateMachine::run() {
    while(!isGameExitTriggered_) {        
        handleEvents();
    
        int nextState = currentState_->gameLoop(stopWatch_.getElaspedTicks());

        if (nextState == exitGameState) {
            isGameExitTriggered_ = true;
            continue;
        } else if (nextState != -1) {
            transition(nextState);
            continue;
        } 
        
        graphicsManager_->render();
    }
}

void GameStateMachine::handleEvents() {
    SDL_Event e;

    while( SDL_PollEvent( &e ) != 0 ) {

        if( e.type == SDL_QUIT ) {
            isGameExitTriggered_ = true;
            return;
        }

        currentState_->handleEvents(&e);
    }
}

void GameStateMachine::transition(int const nextState) {
    if (currentState_ != nullptr) currentState_->exitState();
    
    switch(nextState) {
        case titleScreenStateId: 
            currentState_ = static_cast<GameState*>(new TitleScreenState(graphicsManager_.get(), audioManager_.get(), titleScreenStateId));
        break;
        case worldGeneratorStateId: 
            currentState_ = static_cast<GameState*>(new WorldGeneratorState(graphicsManager_.get(), audioManager_.get(), worldGeneratorStateId));
        break;
    }

    currentState_->enterState();
}