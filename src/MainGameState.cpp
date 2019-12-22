#include "MainGameState.h"
#include "GameState.h"
#include "SharedConstants.h"
#include "Game.h"
#include "KeyboardManager.h"

MainGameState::MainGameState(GraphicsManager* graphics, AudioManager* audio, Game* game) : GameState(graphics, audio) {
    game_ = game;
}

void MainGameState::enterState() {
    buildBackgroundLayer();
    buildButtonLayer();
    buildMapVisualizationLayer();
}

void MainGameState::exitState() {
    backgroundLayer_.reset();
    mapVisualizationLayer_.reset();
}

void MainGameState::update(int elapsedTicks) {

    int offset_x = game_->GetMapView().MapOffsetX();
    int offset_y = game_->GetMapView().MapOffsetY();

    if (game_->GetKeyboardManager().isKeyLeftPressed()) {
        offset_x--;
    }

    if (game_->GetKeyboardManager().isKeyRightPressed()) {
        offset_x++;
    }

    if (game_->GetKeyboardManager().isKeyUpPressed()) {
        offset_y--;
    }

    if (game_->GetKeyboardManager().isKeyDownPressed()) {
        offset_y++;
    }

    mapVisualizationLayer_->setMapOffset(offset_x, offset_y);

    float zoom_level = game_->GetMapView().GetZoomLevel();
    if (game_->GetKeyboardManager().isKeyZoomInPressed()) {
        zoom_level += 0.1f;
    }

    if (game_->GetKeyboardManager().isKeyZoomOutPressed()) {
        zoom_level -= 0.1f;
    }

    mapVisualizationLayer_->setZoomLevel(zoom_level);

    game_->GetMapView().SetMapOffset(offset_x, offset_y);
    game_->GetMapView().SetZoomLevel(zoom_level);
} 

void MainGameState::handleEvents(SDL_Event* e) {
    game_->GetKeyboardManager().UpdateKeyStates(e);
}
    
States MainGameState::nextState() {
    return States::TitleScreen;
}

bool MainGameState::isReadyToTransition() {
    return false;
}

void MainGameState::buildBackgroundLayer() {
    backgroundLayer_ = std::make_unique<BackgroundLayer>(titleScreenBackground, graphics_->getRenderer());
    graphics_->addLayer(static_cast<GraphicsLayer*>(backgroundLayer_.get()));
}

void MainGameState::buildButtonLayer() {}

void MainGameState::buildMapVisualizationLayer() {
    mapVisualizationLayer_ = std::make_unique<MapVisualizationLayer>(graphics_->getRenderer(), gMapTiles);
    mapVisualizationLayer_->setMap(game_->getWorldMap());
    graphics_->addLayer(static_cast<GraphicsLayer*>(mapVisualizationLayer_.get()));
}