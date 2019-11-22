#include <vector>
#include <SDL.h>
#include "Animation.h"

Animation::Animation(const int frameLength) {
    frameLength_ = frameLength;
    elapsedMilliseconds_ = 0;
    frameIndex_ = 0;
}

void Animation::addFrame(SDL_Rect &&frame) {
    frames_.emplace_back(frame);
}

SDL_Rect Animation::update(int elapsedMilliseconds) {
    elapsedMilliseconds_ += elapsedMilliseconds;
    if (elapsedMilliseconds_ < frameLength_) return frames_[frameIndex_];
    
    frameIndex_ = (frameIndex_ + 1) % frames_.size();
    elapsedMilliseconds_ = elapsedMilliseconds_ % frameLength_;

    return frames_[frameIndex_];
}

SDL_Rect Animation::getCurrentFrame() {
    return frames_[frameIndex_];
}
