#ifndef IGRAPHICSLAYER
#define IGRAPHICSLAYER

#include <SDL.h>

class GraphicsLayer {
public:
    GraphicsLayer();

    virtual void render(SDL_Renderer* renderer);
    virtual void updateMouse(int const x, int const y);
    bool isHidden;
};

#endif
