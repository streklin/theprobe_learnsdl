#ifndef WORLDGENERATOR
#define WORLDGENERATOR

#include <mutex>

#include "WorldMap.h"
#include "MapFactory.h"

class WorldGenerator final {
public:
    WorldGenerator();
    void generateWorld();
    bool isCompleted();

    WorldMap* gameWorld() { return gameWorld_; }

private:
    std::mutex mutex_;
    bool isWorldReady_;
    MapFactory factory_;

    WorldMap* gameWorld_;
};

#endif