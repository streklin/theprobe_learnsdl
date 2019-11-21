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

    gameStateFactory_ = GameStateFactory(graphicsManager_.get(), nullptr);
    gameState_ = gameStateFactory_.createState(States::TitleScreen);
    gameState_->enterState();
}

void Game::run() {
    while(!isGameExitTriggered_) {
        handleEvents();
        gameState_->update(stopWatch_.getElaspedTicks());
        graphicsManager_->render();
    }
}

void Game::handleEvents() {
    SDL_Event e;

    while( SDL_PollEvent( &e ) != 0 ) {

        if( e.type == SDL_QUIT ) {
            isGameExitTriggered_ = true;
            return;
        }
    }
}