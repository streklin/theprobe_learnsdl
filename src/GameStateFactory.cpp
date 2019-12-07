#include <memory>

#include "GameStateFactory.h"
#include "TitleScreenState.h"
#include "MapCreationState.h"

GameStateFactory::GameStateFactory() {}

GameStateFactory::GameStateFactory(GraphicsManager* g, AudioManager* a, WorldMap* worldMap) {
    graphics_ = g;
    audio_ = a;
    worldMap_ = worldMap;
}

std::unique_ptr<GameState>  GameStateFactory::createState(States state) {
    switch(state) {
        case States::TitleScreen:
            return createTitleScreenState();
        case States::MapGeneration:
            return createMapGenerationState();
        default:
            throw "No state!";
    };
}

std::unique_ptr<GameState>  GameStateFactory::createTitleScreenState() {
    GameState* s = static_cast<GameState*>(new TitleScreenState(graphics_, audio_));
    return std::unique_ptr<GameState>(s);
}

std::unique_ptr<GameState> GameStateFactory::createMapGenerationState() {
    GameState* s = static_cast<GameState*>(new MapCreationState(graphics_, audio_, worldMap_));
    return std::unique_ptr<GameState>(s);
}