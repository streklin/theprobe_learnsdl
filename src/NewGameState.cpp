#include "NewGameState.h"
#include "PlayerResources.h"
#include "Game.h"

NewGameState::NewGameState(GraphicsManager* graphics, AudioManager* audio, WorldMap* worldMap, Game* game) : GameState(graphics, audio) {
    game_ = game;
    worldMap_ = worldMap;
}

void NewGameState::enterState() {}

void NewGameState::exitState() {}

void NewGameState::update(int elapsedTicks) {
    auto player_resources = PlayerResources();
    game_->setPlayerResources(std::move(player_resources));

    auto start_position = worldMap_->sampleForTile(MapTile::mGrass);
    worldMap_->setTileAt(start_position.first, start_position.second, MapTile::mCity);
} 

States NewGameState::nextState() {
    return States::MainGamePlay;
}

bool NewGameState::isReadyToTransition() {
    return true;
}