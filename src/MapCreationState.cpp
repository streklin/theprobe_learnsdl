#include <thread>

#include "MapFactory.h"
#include "MapCreationState.h"
#include "TitleScreenState.h"
#include "WorldMap.h"

MapCreationState::MapCreationState(GraphicsManager* graphics, AudioManager* audio, WorldMap* worldMap) : GameState(graphics, audio) {
    worldMap_ = worldMap;
}

void MapCreationState::enterState() {
    // create the background layer
    buildBackgroundLayer();
    buildSpriteLayer();
    buildButtonLayer();
    buildMapVisualizationLayer();

    // start the world generator thread
    worldGeneratorThread_ = std::thread([this]() {
        (static_cast<MapCreationState*>(this))->mapFactory_.generateWorld(worldMap_);
    });
}

void MapCreationState::exitState() {
    // clear out objects when exiting state.
    graphics_->clearLayers();
    backgroundLayer_.reset();
    spriteLayer_.reset();
    mapVisualizationLayer_.reset();
}

void MapCreationState::update(int elapsedTicks) {}

void MapCreationState::handleEvents(SDL_Event* e) {}
    
States MapCreationState::nextState() {
    return States::MapGeneration;
}

bool MapCreationState::isReadyToTransition() {
    return false;
}


void MapCreationState::buildBackgroundLayer() {
    backgroundLayer_ = std::make_unique<BackgroundLayer>(titleScreenBackground, graphics_->getRenderer());
    graphics_->addLayer(static_cast<GraphicsLayer*>(backgroundLayer_.get()));
}


void MapCreationState::buildButtonLayer() {
    // stop button

    // accept button

    // regenerate button

    // CONSIDER: Common Button Factory?
}

void MapCreationState::buildSpriteLayer() {
    spriteLayer_ = std::make_unique<SpriteLayer>(graphics_->getRenderer());

    // TO DO: Create loading Sprite
    // CONSIDER: Common Sprite Factory?

    graphics_->addLayer(static_cast<GraphicsLayer*>(spriteLayer_.get()));

}

void MapCreationState::buildMapVisualizationLayer() {
    mapVisualizationLayer_ = std::make_unique<MapVisualizationLayer>(graphics_->getRenderer(), gMapTiles);
    //mapVisualizationLayer_->isHidden = true;
    mapVisualizationLayer_->setMap(worldMap_);
    graphics_->addLayer(static_cast<GraphicsLayer*>(mapVisualizationLayer_.get()));
}