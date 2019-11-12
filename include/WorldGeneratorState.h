#ifndef WORLDGENERATORSTATE
#define WORLDGENERATORSTATE

#include <SDL.h>
#include <memory>
#include <thread>

#include "WorldGenerator.h"
#include "GameState.h"
#include "IGraphicsLayer.h"
#include "Sprite.h"


class WorldGeneratorState final : public GameState {
public:
    WorldGeneratorState(GraphicsManager* manager, AudioManager* audioManager, int const stateId);
    ~WorldGeneratorState();

    void enterState() override;
    void exitState() override;
    int gameLoop(int const elapsedTime) override;
    bool handleEvents(SDL_Event* e) override;
private:
    std::shared_ptr<IGraphicsLayer> backgroundLayer_;
    std::shared_ptr<IGraphicsLayer> spriteLayer_;
    std::shared_ptr<Sprite> loyd_;
    std::thread worldGenerationThread_;

    WorldGenerator generator_;
};

#endif