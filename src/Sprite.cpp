#include <vector>
#include <string>
#include <SDL.h>

#include "Texture.h"
#include "Animation.h"
#include "Sprite.h"

Sprite::Sprite(const std::string spriteSheetPath, SDL_Renderer* renderer) : Texture() {
    loadTexture(spriteSheetPath, renderer);
    currentAnimation_ = 0;
}

void Sprite::render(SDL_Renderer* renderer) {
    SDL_Rect source = animations_[currentAnimation_].getCurrentFrame();
    SDL_Rect target = {x_, y_, source.w * xScale_, source.h * yScale_};

    SDL_RenderCopy( renderer, texture_, &source, &target );
}

void Sprite::update(const int elapsedMilliseconds) {
    animations_[currentAnimation_].update(elapsedMilliseconds);
}

void Sprite::addAnimation(Animation &&animation) {
    animations_.emplace_back(animation);
}

void Sprite::setAnimation(const int animationIndex) {
    if (animationIndex < 0 || animationIndex >= animations_.size()) throw;
    currentAnimation_ = animationIndex;
}