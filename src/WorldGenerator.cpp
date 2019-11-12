#include <iostream>
#include <thread>

#include "WorldGenerator.h"

WorldGenerator::WorldGenerator() {
    isWorldReady_ = false;
}

void WorldGenerator::generateWorld() {
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "World Generation Complete!" << std::endl;

    std::lock_guard<std::mutex> myLock(mutex_);
    isWorldReady_ = true;
}

bool WorldGenerator::isCompleted() {
    std::lock_guard<std::mutex> myLock(mutex_);
    return isWorldReady_;
}