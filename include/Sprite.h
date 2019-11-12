#ifndef SPRITEH
#define SPRITEH

#include <SDL.h>

#include <vector>
#include <string>
#include "Texture.h"
#include "Animation.h"

class Sprite final : public Texture {
public:
    Sprite(std::string const path, SDL_Renderer* renderer);

    void render(SDL_Renderer* renderer) override;
    void addFrame(SDL_Rect const frame);
    void setTranslation(int const x, int const y);
    void addAnimation(Animation anim);
    void setAnimation(const int index);
    void update();

private:
    std::vector<SDL_Rect> frames_;
    std::vector<Animation> animations_;

    int currentAnimationIndex_;

    int x_;
    int y_;
};

#endif