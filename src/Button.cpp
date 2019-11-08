#include <SDL.h>
#include <string>
#include "Button.h"

Button::Button(const std::string path, const int x, const int y, SDL_Renderer* renderer) {
    x_ = x;
    y_ = y;
    loadTexture(path, renderer);

    frameW_ = getWidth();
    frameH_ = getHeight() / 2;
}

void Button::render(SDL_Renderer* renderer) {
    
    SDL_Rect source = {0, 0, frameW_, frameH_};

    if (isMouseOverState_) {
        source.y = frameH_;
    }

    SDL_Rect target = {x_, y_, frameW_ * xScale_, frameH_ * yScale_};

    SDL_RenderCopy( renderer, getTexture(), &source, &target ); 
}

void Button::updateButtonState(int const mouseX, int const mouseY) {
    isMouseOverState_ =  mouseX >= x_ 
                    && mouseX <= x_ + frameW_ * xScale_
                    && mouseY <= y_ + frameH_ * yScale_
                    && mouseY >= y_;
}