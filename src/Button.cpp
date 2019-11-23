#include <memory>
#include <string>
#include <SDL.h>
#include "Sprite.h"
#include "Animation.h"
#include "Button.h"

const int StandardButtonAnimationIndex = 0;
const int HoverButtonAnimationIndex = 1;

Button::Button(const std::string spriteSheet, SDL_Renderer* renderer, const int buttonHeight, const int buttonWidth) {
    sprite_ = std::make_unique<Sprite>(spriteSheet, renderer);

    buttonHeight_ = buttonHeight;
    buttonWidth_ = buttonWidth;

    Animation standardFrame = Animation(0);
    standardFrame.addFrame({0, 0, buttonWidth_, buttonHeight_});

    Animation hoverFrame = Animation(0);
    hoverFrame.addFrame({0, buttonHeight_, buttonWidth_, buttonHeight_});

    sprite_->addAnimation(std::move(standardFrame));
    sprite_->addAnimation(std::move(hoverFrame));

    sprite_->setAnimation(0);

    isButtonClicked_ = false;
    isButtonHovered_ = false;
}

void Button::render(SDL_Renderer* renderer) {
    if (isButtonHovered_) {
        sprite_->setAnimation(HoverButtonAnimationIndex);
    } else {
        sprite_->setAnimation(StandardButtonAnimationIndex);
    }

    sprite_->render(renderer);
}

void Button::handleEvents(SDL_Event* e) {
    int x, y;
    SDL_GetMouseState( &x, &y );
    isButtonHovered_ = isMouseOver(x, y);
    isButtonClicked_ = ( e->type == SDL_MOUSEBUTTONDOWN && isButtonHovered_);
}

bool Button::isClicked() {
    return isButtonClicked_;
}

bool Button::isMouseOver(const int mouseX, const int mouseY) {
   return   mouseX >= sprite_->getX() 
            && mouseX <= sprite_->getX() + buttonWidth_ * sprite_->getXScale()
            && mouseY <= sprite_->getY() + buttonHeight_  * sprite_->getYScale()
            && mouseY >= sprite_->getY();
}

void Button::setPosition(const int x, const int y) {
    sprite_->setPosition(x, y);
}

void Button::setScale(const int xScale, const int yScale) {
    sprite_->setScale(xScale, yScale);
}