#ifndef TITLESCREENSTATE
#define TITLESCREENSTATE

#include <string>
#include <memory>

#include "GameState.h"
#include "BackgroundLayer.h"

const std::string titleScreenBackground = "images/Space1.png";

class TitleScreenState : public GameState {
public:
    TitleScreenState(GraphicsManager* graphics, AudioManager* audio);

    void enterState() override;
    void exitState() override;
    void update(int elapsedTicks) override; 
    States nextState() override;
    bool isReadyToTransition() override;

private:
    std::unique_ptr<BackgroundLayer> backgroundLayer_;
};

#endif