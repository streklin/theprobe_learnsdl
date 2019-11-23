#ifndef BUTTON
#define BUTTON

#include <memory>
#include <string>
#include <SDL.h>
#include "Sprite.h"

class Button {
public:
    Button(const std::string spriteSheet, SDL_Renderer* renderer, const int buttonHeight, const int buttonWidth);

    void render(SDL_Renderer* renderer);
    void handleEvents(SDL_Event* e);
    bool isClicked();

    void setPosition(const int x, const int y);
    void setScale(const int xScale, const int yScale);
private:

    bool isMouseOver(const int mouseX, const int mouseY);

    std::unique_ptr<Sprite> sprite_;
    bool isButtonClicked_;
    bool isButtonHovered_;
    int buttonHeight_;
    int buttonWidth_;
};

#endif