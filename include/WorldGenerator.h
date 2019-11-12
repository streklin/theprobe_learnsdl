#ifndef WORLDGENERATOR
#define WORLDGENERATOR

#include <mutex>

class WorldGenerator final {
public:
    WorldGenerator();
    void generateWorld();
    bool isCompleted();
private:
    std::mutex mutex_;
    bool isWorldReady_;
};

#endif