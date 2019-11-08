#include<string>
#include <SDL.h>
#include "Panel.h"

Panel::Panel(std::string const path, int const x, int const y, SDL_Renderer* renderer) {
    x_ = x;
    y_ = y;
    loadTexture(path, renderer);
}

void Panel::render(SDL_Renderer* renderer) {
    SDL_Rect target = {x_, y_, getWidth() * xScale_, getHeight() * yScale_};
    SDL_RenderCopy( renderer, getTexture(), NULL, &target ); 
}
