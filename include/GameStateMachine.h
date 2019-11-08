#ifndef GAMESTATEMACHINE
#define GAMESTATEMACHINE

#include <memory>
#include <vector>
#include <map>

#include "GameState.h"
#include "GraphicsManager.h"
#include "AudioManager.h"
#include "TitleScreenState.h"
#include "WorldGeneratorState.h"
#include "StopWatch.h"

class GameStateMachine final {
public:
    GameStateMachine();
    void run();

private:    
    void initializeManagerObjects();
    void initializeStates();

    void handleEvents();
    void transition(const int nextState);

    GameState* currentState_; // pointer to the current game state, this pointer is not the owner
    
    StopWatch stopWatch_;

    bool isGameExitTriggered_;

    std::unique_ptr<GraphicsManager> graphicsManager_;
    std::unique_ptr<AudioManager> audioManager_;

    // states
    std::unique_ptr<TitleScreenState> titleScreenState_;
    std::unique_ptr<WorldGeneratorState> worldGeneratorState_;



};

#endif