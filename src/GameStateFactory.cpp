#include <memory>

#include "GameStateFactory.h"
#include "TitleScreenState.h"

GameStateFactory::GameStateFactory() {}

GameStateFactory::GameStateFactory(GraphicsManager* g, AudioManager* a) {
    graphics_ = g;
    audio_ = a;
}

std::unique_ptr<GameState>  GameStateFactory::createState(States state) {
    switch(state) {
        case States::TitleScreen:
            return createTitleScreenState();
        default:
            throw "No state!";
    };
}

std::unique_ptr<GameState>  GameStateFactory::createTitleScreenState() {
    GameState* s = static_cast<GameState*>(new TitleScreenState(graphics_, audio_));
    return std::unique_ptr<GameState>(s);
};