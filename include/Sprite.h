#ifndef SPRITE
#define SPRITE

#include <vector>
#include <string>
#include <SDL.h>

#include "Texture.h"
#include "Animation.h"

class Sprite final : public Texture {
    Sprite(const std::string spriteSheetPath, SDL_Renderer* renderer);

    void render(SDL_Renderer* renderer) override;
    void update(const int elapsedMilliseconds);
    void addAnimation(Animation &&animation);
    void setAnimation(const int animationIndex);

private:
    std::vector<Animation> animations_;
    int currentAnimation_;
};

#endif