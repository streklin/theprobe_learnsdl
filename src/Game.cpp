#include <memory>

#include "GraphicsManager.h"
#include "Game.h"

const int gScreenWidth = 1280;
const int gScreenHeight = 960;

Game::Game() {
    graphicsManager_ = std::make_unique<GraphicsManager>(gScreenWidth, gScreenHeight);
    graphicsManager_->init();
}

void Game::run() {
    
}