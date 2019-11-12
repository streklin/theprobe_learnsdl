#include <SDL.h>
#include <memory>
#include <vector>
#include <iostream>
#include <thread>
#include <future>

#include "stateIdList.h"
#include "AudioManager.h"
#include "SimpleBackgroundLayer.h"
#include "SpriteLayer.h"
#include "GameState.h"
#include "IGraphicsLayer.h"
#include "Sprite.h"
#include "Animation.h"
#include "WorldGeneratorState.h"


WorldGeneratorState::WorldGeneratorState(GraphicsManager* manager, AudioManager* audioManager, int const stateId) : GameState(manager, audioManager, stateId) {
    backgroundLayer_ = std::shared_ptr<IGraphicsLayer>(static_cast<IGraphicsLayer*>(new SimpleBackgroundLayer("images/Space2.png", manager->renderer())));
    spriteLayer_ = std::shared_ptr<IGraphicsLayer>(static_cast<IGraphicsLayer*> (new SpriteLayer()));
}

WorldGeneratorState::~WorldGeneratorState() {
    worldGenerationThread_.join();
}

void WorldGeneratorState::enterState() {

    std::cout << "Start World Generator State" << std::endl;

    std::cout << "Add Layers" << std::endl;
    graphicsManager_->clearLayers();
    graphicsManager_->addLayer(backgroundLayer_);
    graphicsManager_->addLayer(spriteLayer_);

    /*
    Load the appropriate sprites.
    */
    std::cout << "Create Sprite" << std::endl;
    loyd_ = std::shared_ptr<Sprite>(new Sprite("images/Loyd.png", graphicsManager_->renderer()));
    loyd_->addFrame({0,0,48, 72});
    loyd_->addFrame({48,0,48,72});
    loyd_->addFrame({96,0,48,72});


    Animation animation({0,1,2});
    animation.setAnimationSpeed(250);

    loyd_->addAnimation(animation);

    loyd_->setAnimation(0);

    SpriteLayer* l = static_cast<SpriteLayer*>(spriteLayer_.get());
    l->addSprite(loyd_);

    worldGenerationThread_ = std::thread([this]() {
        std::cout << "Starting World Generation ..." << std::endl;
        (static_cast<WorldGeneratorState*>(this))->generator_.generateWorld();
    }); 
}

void WorldGeneratorState::exitState() {
    SpriteLayer* l = static_cast<SpriteLayer*>(spriteLayer_.get());
    l->clearSprites();
}

int WorldGeneratorState::gameLoop(int const elapsedTime) {

    if (generator_.isCompleted()) {
        std::cout << "Thread Completed it's work!" << std::endl;
    }

    return -1;
}

bool WorldGeneratorState::handleEvents(SDL_Event* e) {
    return true;
}
