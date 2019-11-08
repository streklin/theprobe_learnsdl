#ifndef GRAPHICSMANAGER
#define GRAPHICSMANAGER

#include <SDL.h>
#include <vector>
#include <string>
#include <memory>

#include "IGraphicsLayer.h"

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

class GraphicsManager final {
public:
    GraphicsManager(int const screenWidth, int const screenHeight);
    ~GraphicsManager();

    bool init();
    void close();
    void addLayer(std::shared_ptr<IGraphicsLayer> layer);
    void clearLayers();
    void render();

    SDL_Renderer* renderer();

private:
    int screenWidth_;
    int screenHeight_;

    SDL_Window* window_;
    SDL_Renderer* renderer_;

    std::vector<std::shared_ptr<IGraphicsLayer>> layers_;

};

#endif