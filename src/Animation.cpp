#include <vector>
#include <iostream>

#include "Animation.h"

Animation::Animation() {
    frameIdx_ = 0;
    tickCounter_ = 0;
}

Animation::Animation(std::vector<int> const frames) {
    frameIndices_ = frames;
    frameIdx_ = 0;
    tickCounter_ = 0;
}

void Animation::addFrameIndex(const int frameIdx) {
    frameIndices_.emplace_back(frameIdx);
}

void Animation::update() {

    const int elapsedTicks = stopWatch.getElaspedTicks();
    tickCounter_ += elapsedTicks;

    if (tickCounter_ < animationSpeed_) return;

    frameIdx_ = (frameIdx_ + 1) % frameIndices_.size();
    tickCounter_ = tickCounter_ % animationSpeed_;
}

int Animation::currentFrame() { 
    return frameIndices_[frameIdx_];
}

void Animation::setAnimationSpeed(const int animationSpeed) {
    animationSpeed_ = animationSpeed;
}
