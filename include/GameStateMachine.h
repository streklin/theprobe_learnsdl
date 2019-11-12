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
#include "WorldMap.h"

class GameStateMachine final {
public:
    GameStateMachine();
    void run();

private:    
    void initializeManagerObjects();
    void handleEvents();
    void transition(const int nextState);

    GameState* currentState_; // pointer to the current game state, this pointer is not the owner
    
    StopWatch stopWatch_;

    bool isGameExitTriggered_;

    std::unique_ptr<GraphicsManager> graphicsManager_;
    std::unique_ptr<AudioManager> audioManager_;

    std::shared_ptr<WorldMap> worldMap_;

};

#endif