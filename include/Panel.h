#ifndef PANEL
#define PANEL

#include <SDL.h>
#include <string>
#include "Texture.h"

class Panel final : public Texture {
public:
    Panel(std::string const path, int const x, int const y, SDL_Renderer* renderer);

    void render(SDL_Renderer* renderer) override;

private:
    int x_;
    int y_;
};

#endif