#ifndef GAMESTATEFACTORY
#define GAMESTATEFACTORY

#include <memory>

#include "GraphicsManager.h"
#include "AudioManager.h"
#include "GameState.h"

class GameStateFactory final {
public:
    GameStateFactory();
    GameStateFactory(GraphicsManager* g, AudioManager* a);

    std::unique_ptr<GameState> createState(States state); // returns a data handle, does not manage
private:
    std::unique_ptr<GameState> createTitleScreenState();

    GraphicsManager* graphics_; // non owning
    AudioManager* audio_; //  non owning
};

#endif