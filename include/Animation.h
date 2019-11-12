#ifndef ANIMATION
#define ANIMATION

#include <vector>
#include "StopWatch.h"

class Animation {
public:
    Animation();
    Animation(std::vector<int> frameIndices);

    void addFrameIndex(const int frameIdx);
    void update();
    void setAnimationSpeed(const int animationSpeed);
    int currentFrame();

private:
    std::vector<int> frameIndices_;
    StopWatch stopWatch;
    int tickCounter_;
    int animationSpeed_;
    int frameIdx_;
};

#endif