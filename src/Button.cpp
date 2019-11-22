#include <memory>
#include <string>
#include <SDL.h>
#include "Sprite.h"
#include "Animation.h"
#include "Button.h"

Button::Button(const std::string spriteSheet, SDL_Renderer* renderer, const int buttonHeight, const int buttonWidth) {
    sprite_ = std::make_unique<Sprite>(spriteSheet, renderer);

    buttonHeight_ = buttonHeight;
    buttonWidth_ = buttonWidth_;

    Animation standardFrame;
    standardFrame.addFrame({0, 0, buttonWidth_, buttonHeight_});

    Animation hoverFrame;
    hoverFrame.addFrame({0, buttonHeight_, buttonWidth_, buttonHeight_});

    sprite_->addAnimation(std::move(standardFrame));
    sprite_->addAnimation(std::move(hoverFrame));

    sprite_->setAnimation(0);

    isButtonClicked_ = false;
    isButtonHovered_ = false;
}

void Button::render(SDL_Renderer* renderer) {
    // check if hover
        // yes, set animation to hover
        // no, set to standard
    // call the sprites render function.
}

void Button::handleEvents(SDL_Event* e) {
    // check if the mouse is over the button

    // is the mouse button pressed?
}

bool Button::isClicked() {
    return isButtonClicked_;
}