#ifndef GAME
#define GAME

#include <vector>
#include <memory>

#include "GraphicsManager.h"
#include "GameState.h"

class Game final {
public:
    Game();
    void run();

private:
    std::unique_ptr<GraphicsManager> graphicsManager_;
    std::unique_ptr<GameState> currentState_;
};

#endif