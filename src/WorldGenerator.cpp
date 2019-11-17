#include <iostream>
#include <thread>

#include "MapFactory.h"
#include "WorldGenerator.h"

WorldGenerator::WorldGenerator() {
    isWorldReady_ = false;
    factory_ = MapFactory(MAP_WIDTH, MAP_HEIGHT, 5000);
}

void WorldGenerator::generateWorld() {
    std::cout << "Generating World ... \n";
    gameWorld_ = factory_.generateNewWorld(0);
    std::cout << "World Generation Complete! \n";

    std::lock_guard<std::mutex> myLock(mutex_);
    isWorldReady_ = true;
}

bool WorldGenerator::isCompleted() {
    std::lock_guard<std::mutex> myLock(mutex_);
    return isWorldReady_;
}