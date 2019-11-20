#ifndef GAMESTATE
#define GAMESTATE

#include <vector>

#include "AudioManager.h"
#include "GraphicsManager.h"

enum States {
    TitleScreen,
    MapGeneration,
    MainGamePlay,
    Loading,
    Crafting,
    Upgrading
};

class GameState {
public:
    GameState(GraphicsManager* graphics, AudioManager* audio);
    ~GameState();

    virtual void enterState();
    virtual void exitState();
    virtual void update(int elapsedTicks); 
    virtual State nextState();

    virtual bool isReadyToTransition();

private:
    GraphicsManager* graphics_; // data handle, not owned
    AudioManager* audio_; //data handle, not owned.
    std::vector<State> children_; // data handles, not owned, used for transitions.
    bool isReadyToTransition_; // start state transition when true
};

#endif