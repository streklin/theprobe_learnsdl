#ifndef GAME
#define GAME

#include <vector>
#include <memory>

#include "GameStateFactory.h"
#include "GraphicsManager.h"
#include "GameState.h"
#include "StopWatch.h"
#include "WorldMap.h"

class Game final {
public:
    Game();
    void run();

private:
    void handleEvents();
    void transitionToNextState(States state);

    bool isGameExitTriggered_;
    std::unique_ptr<GraphicsManager> graphicsManager_;
    std::unique_ptr<GameState> gameState_;
    std::unique_ptr<WorldMap> worldMap_;

    GameStateFactory gameStateFactory_;
    StopWatch stopWatch_;
};

#endif