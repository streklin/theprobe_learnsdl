#include <memory>
#include <thread>
#include <SDL.h>
#include <iostream>

#include "GraphicsManager.h"
#include "Game.h"

const int gScreenWidth = 1280;
const int gScreenHeight = 960;

Game::Game() {
    graphicsManager_ = std::make_unique<GraphicsManager>(gScreenWidth, gScreenHeight);
    graphicsManager_->init();
    isGameExitTriggered_ = false;

    worldMap_ = std::make_unique<WorldMap>();

    gameStateFactory_ = GameStateFactory(graphicsManager_.get(), nullptr, worldMap_.get(), this);
    gameState_ = gameStateFactory_.createState(States::TitleScreen);
    gameState_->enterState();

    map_view_ = MapView();
    keyboard_manager_ = KeyboardManager();
}

void Game::run() {
    while(!isGameExitTriggered_) {
        handleEvents();
        gameState_->update(stopWatch_.getElaspedTicks());
        
        // check for transition
        if (gameState_->isReadyToTransition()) {
            auto nextState = gameState_->nextState();

            if (nextState == States::ExitGame) {
                isGameExitTriggered_ = true;
                continue;
            }

            transitionToNextState(nextState);
        }
        
        graphicsManager_->render();
    }
}

WorldMap* Game::getWorldMap() {
    return worldMap_.get();
}

void Game::handleEvents() {
    SDL_Event e;

    while( SDL_PollEvent( &e ) != 0 ) {

        if( e.type == SDL_QUIT ) {
            isGameExitTriggered_ = true;
            return;
        }

        gameState_->handleEvents(&e);
    }
}

void Game::transitionToNextState(States nextState) {
    gameState_->exitState();
    gameState_.reset();
    gameState_ = gameStateFactory_.createState(nextState);
    gameState_->enterState();
}

void Game::setPlayerResources(PlayerResources resources) {
    resources_ = resources;
}

PlayerResources& Game::GetPlayerResources() {
    return resources_;
}

MapView& Game::GetMapView() {
    return map_view_;
}

KeyboardManager& Game::GetKeyboardManager() {
    return keyboard_manager_;
}