#ifndef TITLESCREENSTATE
#define TITLESCREENSTATE

#include <SDL.h>
#include <memory>

#include "GameState.h"
#include "IGraphicsLayer.h"
#include "TitleScreenUXLayer.h"

class TitleScreenState final : public GameState {
public:
    TitleScreenState(GraphicsManager* manager, AudioManager* audioManager, int const stateId);

    void enterState() override;
    void exitState() override;
    int gameLoop(int const elapsedTime) override;
    bool handleEvents(SDL_Event* e) override;

private:
    std::shared_ptr<IGraphicsLayer> backgroundLayer_;
    std::shared_ptr<IGraphicsLayer> uxLayer_;

    bool exitState_;
};

#endif