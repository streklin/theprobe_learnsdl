#ifndef TITLESCREENSTATE
#define TITLESCREENSTATE

#include <memory>

#include "GameState.h"
#include "GraphicsLayer.h"

class TitleScreenState : public GameState {
public:
    TitleScreenState(GraphicsManager* graphics, AudioManager* audio);

    void enterState() override;
    void exitState() override;
    void update(int elapsedTicks) override; 
    State nextState() override;
    bool isReadyToTransition() override;

private:

}

#endif