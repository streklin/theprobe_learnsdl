#ifndef IGRAPHICSLAYER
#define IGRAPHICSLAYER

#include <SDL.h>

class GraphicsLayer {
public:
    GraphicsLayer(SDL_Renderer* renderer);

    virtual void render();
    virtual void updateMouse(int const x, int const y);
    bool isHidden;

protected:
    SDL_Renderer* renderer_;
};

#endif
