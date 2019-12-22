#include <thread>
#include <iostream>

#include "MapFactory.h"
#include "MapCreationState.h"
#include "TitleScreenState.h"
#include "WorldMap.h"

MapCreationState::MapCreationState(GraphicsManager* graphics, AudioManager* audio, WorldMap* worldMap) : GameState(graphics, audio) {
    worldMap_ = worldMap;
}

void MapCreationState::enterState() {
    buildButtonLayer();
    buildMapVisualizationLayer();
    generateNewMap();
}

void MapCreationState::generateNewMap() {
    if (!mapFactory_.isReady()) return;

    worldGeneratorThread_ = std::thread([this]() {
        (static_cast<MapCreationState*>(this))->mapFactory_.generateWorld(worldMap_);
    });
}

void MapCreationState::exitState() {
    graphics_->clearLayers();

    mapVisualizationLayer_.reset();
    buttonLayer_.reset();
    
    worldGeneratorThread_.join();
}

void MapCreationState::update(int elapsedTicks) {
    if (regenerateWorldBtn_->isClicked()) {
        worldGeneratorThread_.join();
        generateNewMap();
    }

    if (exitGameBtn_->isClicked()) {
        isReadyToTransition_ = true;
        transitionState = States::ExitGame;
    }

    if (enterWorldBtn_->isClicked()) {
        isReadyToTransition_ = true;
        transitionState = States::NewGame;
    }
}

void MapCreationState::handleEvents(SDL_Event* e) {
    buttonLayer_->handleEvents(e);
}
    
States MapCreationState::nextState() {
    return transitionState;
}

bool MapCreationState::isReadyToTransition() {
    return isReadyToTransition_;
}

void MapCreationState::buildBackgroundLayer() {
    backgroundLayer_ = std::make_unique<BackgroundLayer>(titleScreenBackground, graphics_->getRenderer());
    graphics_->addLayer(static_cast<GraphicsLayer*>(backgroundLayer_.get()));
}

void MapCreationState::buildButtonLayer() {

    regenerateWorldBtn_ = std::make_unique<Button>("images/StartGameBtn.png", graphics_->getRenderer(), 65, 103);
    regenerateWorldBtn_->setPosition(0, 890);
    regenerateWorldBtn_->setScale(2.0, 1.0);

    exitGameBtn_ = std::make_unique<Button>("images/StartGameBtn.png", graphics_->getRenderer(), 65, 103);
    exitGameBtn_->setPosition(220, 890);
    exitGameBtn_->setScale(2.0, 1.0);

    enterWorldBtn_ = std::make_unique<Button>("images/StartGameBtn.png", graphics_->getRenderer(), 65, 103);
    enterWorldBtn_->setPosition(460, 890);
    enterWorldBtn_->setScale(2.0, 1.0);


    buttonLayer_ = std::make_unique<ButtonLayer>(graphics_->getRenderer());
    buttonLayer_->addButton(regenerateWorldBtn_.get());
    buttonLayer_->addButton(exitGameBtn_.get());
    buttonLayer_->addButton(enterWorldBtn_.get());

    graphics_->addLayer(static_cast<GraphicsLayer*>(buttonLayer_.get()));
}


void MapCreationState::buildMapVisualizationLayer() {
    mapVisualizationLayer_ = std::make_unique<MapVisualizationLayer>(graphics_->getRenderer(), gMapTiles);
    mapVisualizationLayer_->setMap(worldMap_);
    graphics_->addLayer(static_cast<GraphicsLayer*>(mapVisualizationLayer_.get()));
}