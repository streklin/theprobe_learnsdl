#ifndef GAMESTATE
#define GAMESTATE

#include <vector>

#include "AudioManager.h"
#include "GraphicsManager.h"

enum States {
    TitleScreen,
    ExitGame,
    MapGeneration,
    NewGame,
    MainGamePlay,
    Loading,
    Crafting,
    Upgrading
};

class GameState {
public:
    GameState();
    GameState(GraphicsManager* graphics, AudioManager* audio);
    
    ~GameState();

    virtual void enterState();
    virtual void exitState();
    virtual void update(int elapsedTicks); 
    virtual States nextState();
    virtual void handleEvents(SDL_Event* e);

    virtual bool isReadyToTransition();

protected:
    GraphicsManager* graphics_; // data handle, not owned
    AudioManager* audio_; //data handle, not owned.
    std::vector<States> children_; // data handles, not owned, used for transitions.
    bool isReadyToTransition_; // start state transition when true
};

#endif