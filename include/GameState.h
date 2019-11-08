#ifndef GAMESTATE
#define GAMESTATE

#include "AudioManager.h"
#include "GraphicsManager.h"

class GameState {
public:
    GameState(GraphicsManager* manager, AudioManager* audioManager, int const stateId);
    
    virtual void enterState();
    virtual void exitState();
    virtual int gameLoop(int const elapsedTime);
    virtual bool handleEvents(SDL_Event* e);

    int stateId();

protected:
    GraphicsManager* graphicsManager_; 
    AudioManager* audioManager_;
    int stateId_;
};

#endif