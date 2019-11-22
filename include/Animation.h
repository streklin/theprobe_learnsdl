#ifndef ANIMATION
#define ANIMATION

#include <vector>
#include <SDL.h>

class Animation final {
public:
    Animation(const int frameLength);

    void addFrame(SDL_Rect &&frame);
    SDL_Rect update(int elapsedMilliseconds);
    SDL_Rect getCurrentFrame();

private:
    std::vector<SDL_Rect> frames_;

    int elapsedMilliseconds_;
    int frameLength_;
    int frameIndex_;

};

#endif