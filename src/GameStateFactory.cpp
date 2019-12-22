#include <memory>

#include "GameStateFactory.h"
#include "TitleScreenState.h"
#include "MapCreationState.h"
#include "NewGameState.h"
#include "MainGameState.h"
#include "Game.h"

GameStateFactory::GameStateFactory() {}

GameStateFactory::GameStateFactory(GraphicsManager* g, AudioManager* a, WorldMap* worldMap, Game* game) {
    graphics_ = g;
    audio_ = a;
    worldMap_ = worldMap;
    game_ = game;
}

std::unique_ptr<GameState>  GameStateFactory::createState(States state) {
    switch(state) {
        case States::TitleScreen:
            return createTitleScreenState();
        case States::MapGeneration:
            return createMapGenerationState();
        case States::NewGame:
            return createNewGameState();
        case States::MainGamePlay:
            return createMainGameState();
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

std::unique_ptr<GameState> GameStateFactory::createNewGameState() {
    GameState* s = static_cast<GameState*>(new NewGameState(graphics_, audio_, worldMap_, game_));
    return std::unique_ptr<GameState>(s);
}

std::unique_ptr<GameState> GameStateFactory::createMainGameState() {
    GameState* s = static_cast<GameState*>(new MainGameState(graphics_, audio_, game_));
    return std::unique_ptr<GameState>(s);
}