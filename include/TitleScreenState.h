#ifndef TITLESCREENSTATE
#define TITLESCREENSTATE

#include <string>
#include <memory>

#include "GameState.h"
#include "BackgroundLayer.h"
#include "StaticTextureLayer.h"
#include "Texture.h"

const std::string titleScreenBackground = "images/TitleBG.png";
const std::string hudTexture = "images/HUD.png";

class TitleScreenState : public GameState {
public:
    TitleScreenState(GraphicsManager* graphics, AudioManager* audio);

    void enterState() override;
    void exitState() override;
    void update(int elapsedTicks) override; 
    States nextState() override;
    bool isReadyToTransition() override;

private:
    void buildBackgroundLayer();
    void buildStaticTextureLayer();
    
    std::unique_ptr<BackgroundLayer> backgroundLayer_;
    std::unique_ptr<StaticTextureLayer> staticTextureLayer_;
    std::unique_ptr<Texture> hudTexture_;


};

#endif