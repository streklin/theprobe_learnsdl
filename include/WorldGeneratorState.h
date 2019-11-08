#ifndef WORLDGENERATORSTATE
#define WORLDGENERATORSTATE

#include <SDL.h>
#include <memory>

#include "GameState.h"
#include "IGraphicsLayer.h"

class WorldGeneratorState final : public GameState {
public:
    WorldGeneratorState(GraphicsManager* manager, AudioManager* audioManager, int const stateId);

    void enterState() override;
    void exitState() override;
    int gameLoop(int const elapsedTime) override;
    bool handleEvents(SDL_Event* e) override;
private:
    std::shared_ptr<IGraphicsLayer> backgroundLayer_;
};

#endif