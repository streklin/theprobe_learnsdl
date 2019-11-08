#ifndef BUTTON
#define BUTTON

#include <SDL.h>
#include <string>
#include "Texture.h"

// Button Assumes frames are vertically stacked.
class Button final : public Texture {
public:
    Button(const std::string path, const int x, const int y, SDL_Renderer* renderer);

    void render(SDL_Renderer* renderer) override;
    void updateButtonState(const int mouseX, const int mouseY);

private:
    bool isMouseOverState_;

    int x_;
    int y_;
    int frameW_;
    int frameH_;
};

#endif