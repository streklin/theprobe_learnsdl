#ifndef MAPCREATIONSTATE
#define MAPCREATIONSTATE

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

class MapCreationState final : public GameState {
public:
    MapCreationState(GraphicsManager* graphics, AudioManager* audio, WorldMap* worldMap);

    void enterState() override;
    void exitState() override;
    void update(int elapsedTicks) override; 
    void handleEvents(SDL_Event* e) override;
    
    States nextState() override;
    bool isReadyToTransition() override;
private:
    void buildBackgroundLayer();
    void buildButtonLayer();
    void buildSpriteLayer();
    void buildMapVisualizationLayer();

    std::unique_ptr<BackgroundLayer> backgroundLayer_;
    std::unique_ptr<SpriteLayer> spriteLayer_;
    std::unique_ptr<MapVisualizationLayer> mapVisualizationLayer_;
    std::unique_ptr<ButtonLayer> buttonLayer_;

    std::thread worldGeneratorThread_;

    MapFactory mapFactory_;
    WorldMap* worldMap_;
};

#endif