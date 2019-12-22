#ifndef TITLESCREENSTATE
#define TITLESCREENSTATE

#include <string>
#include <memory>

#include "GameState.h"
#include "BackgroundLayer.h"
#include "StaticTextureLayer.h"
#include "ButtonLayer.h"
#include "Button.h"
#include "Texture.h"
#include "FontTexture.h"
#include "SharedConstants.h"


class TitleScreenState final : public GameState {
public:
    TitleScreenState(GraphicsManager* graphics, AudioManager* audio);

    void enterState() override;
    void exitState() override;
    void update(int elapsedTicks) override; 
    void handleEvents(SDL_Event* e) override;
    
    States nextState() override;
    bool isReadyToTransition() override;

private:
    void buildBackgroundLayer();
    void buildStaticTextureLayer();
    void buildButtonLayer();
    
    std::unique_ptr<BackgroundLayer> backgroundLayer_;
    std::unique_ptr<StaticTextureLayer> staticTextureLayer_;
    std::unique_ptr<ButtonLayer> buttonLayer_;

    std::unique_ptr<Texture> hudTexture_;
    std::unique_ptr<Button> startGameBtn_;
    std::unique_ptr<Button> exitGameBtn_;

    States transitionState;

};

#endif