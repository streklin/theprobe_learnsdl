#ifndef NEWGAMESTATE
#define NEWGAMESTATE

#include <SDL.h>
#include <thread>
#include <memory>

#include "Game.h"
#include "GameState.h"
#include "WorldMap.h"
#include "BackgroundLayer.h"

class NewGameState final : public GameState {
public:
    NewGameState(GraphicsManager* graphics, AudioManager* audio, WorldMap* worldMap, Game* game);

    void enterState() override;
    void exitState() override;
    void update(int elapsedTicks) override; 

    States nextState() override;
    bool isReadyToTransition() override;

private:
    Game* game_;
    WorldMap* worldMap_;
};

#endif