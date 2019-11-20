#include "GameStateFactory.h"

GameStateFactory::GameStateFactory() {}

GameState* GameStateFactory::createState(States state) {
    switch(state) {
        case States::TitleScreen:
            return createTitleScreenState();
        default:
            throw "No state!";
    };
}

GameState* GameStateFactory::createTitleScreenState() {
    
};