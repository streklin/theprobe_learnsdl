#include <SDL.h>

#include <vector>
#include <string>
#include <iostream>

#include "Animation.h"
#include "Sprite.h"

Sprite::Sprite(std::string const path, SDL_Renderer* renderer) {
    loadTexture(path, renderer);
    currentAnimationIndex_ = 0;
    x_ = 0;
    y_ = 0;
}

void Sprite::render(SDL_Renderer* renderer) {

    int frameIdx = animations_[currentAnimationIndex_].currentFrame();
    
    SDL_Rect source = frames_[frameIdx];
    SDL_Rect target = {x_, y_, source.w, source.h};

    SDL_RenderCopy(renderer, getTexture(), &source, &target);
}

void Sprite::addFrame(SDL_Rect const frame) {
    frames_.emplace_back(frame);
}

void Sprite::setTranslation(int const x, int const y) {
    x_ = x;
    y_ = y;
}

void Sprite::addAnimation(Animation anim) {
    animations_.emplace_back(anim);
}

void Sprite::setAnimation(const int index) {
    currentAnimationIndex_ = index;
}

void Sprite::update() {
    animations_[currentAnimationIndex_].update();
}