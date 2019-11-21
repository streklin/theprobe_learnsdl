#include <SDL.h>
#include "StopWatch.h"

StopWatch::StopWatch() {
    startTime_ = SDL_GetTicks();
    lastTicks_ = startTime_;
}

int StopWatch::getElaspedTicks() {
    Uint32 currentTime = SDL_GetTicks();
    int result = currentTime - lastTicks_;
    lastTicks_ = currentTime;

    return result;
}

int StopWatch::getTotalTicks() {
    return SDL_GetTicks() - startTime_;
}

int StopWatch::reset() {
    startTime_ = SDL_GetTicks();
    lastTicks_ = startTime_;
}