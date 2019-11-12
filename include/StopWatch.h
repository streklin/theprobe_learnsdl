#ifndef STOPWATCH
#define STOPWATCH

#include <SDL.h>

class StopWatch final {
public:
    StopWatch();

    int getElaspedTicks();
    int getTotalTicks();
    int reset();
private:
    Uint32 startTime_;
    Uint32 lastTicks_;
};

#endif