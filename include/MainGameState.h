#ifndef MAINGAMESTATE
#define MAINGAMESTATE

#include <SDL.h>
#include <thread>
#include <memory>

#include "GameState.h"
#include "BackgroundLayer.h"
#include "StaticTextureLayer.h"
#include "ButtonLayer.h"
#include "SpriteLayer.h"
#include "MapVisualizationLayer.h"
#include "WorldMap.h"
#include "MapFactory.h"

class Game;

class MainGameState final : public GameState {
public:
    MainGameState(GraphicsManager* graphics, AudioManager* audio, Game* game);

    void enterState() override;
    void exitState() override;
    void update(int elapsedTicks) override; 
    void handleEvents(SDL_Event* e) override;
    
    States nextState() override;
    bool isReadyToTransition() override;

private:
    void buildBackgroundLayer();
    void buildButtonLayer();
    void buildMapVisualizationLayer();


    std::unique_ptr<BackgroundLayer> backgroundLayer_;
    std::unique_ptr<MapVisualizationLayer> mapVisualizationLayer_;
    std::unique_ptr<ButtonLayer> buttonLayer_;
    std::unique_ptr<SpriteLayer> spriteLayer_;

    Game* game_;
};

#endif