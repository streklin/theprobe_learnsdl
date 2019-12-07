#ifndef SPRITE
#define SPRITE

#include <vector>
#include <string>
#include <SDL.h>

#include "Texture.h"
#include "Animation.h"

class Sprite final : public Texture {
public:
    Sprite(const std::string spriteSheetPath, SDL_Renderer* renderer);

    void render(SDL_Renderer* renderer) override;
    void renderAt(SDL_Renderer* renderer, const int x, const int y);
    void update(const int elapsedMilliseconds);
    void addAnimation(Animation &&animation);
    void setAnimation(const int animationIndex);

private:
    std::vector<Animation> animations_;
    int currentAnimation_;
};

#endif