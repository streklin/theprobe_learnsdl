#ifndef IGRAPHICSLAYER
#define IGRAPHICSLAYER

#include <SDL.h>

class IGraphicsLayer {
public:
    IGraphicsLayer();

    virtual void render(SDL_Renderer* renderer);
    virtual void updateMouse(int const x, int const y);
    bool isHidden;
};

#endif
