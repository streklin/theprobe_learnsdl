#include <SDL.h>
#include <memory>
#include "Button.h"
#include "Panel.h"
#include "IGraphicsLayer.h"
#include "TitleScreenUXLayer.h"

const float panelXScale = 0.5f;
const float panelYScale = 1.0f;

const float buttonXScale = 2.0f;
const float buttonYScale = 1.0f;


TitleScreenUXLayer::TitleScreenUXLayer(SDL_Renderer* renderer) {
    mainPanel_ = std::make_unique<Panel>(Panel("images/HUD.png", 705, 50, renderer));
    mainPanel_->setScale(panelXScale, panelYScale);

    startGameBtn_ = std::make_unique<Button>( Button("images/Button.png", 840, 200, renderer) );
    startGameBtn_->setScale(buttonXScale, buttonYScale);

    exitGameBtn_ = std::make_unique<Button> ( Button("images/Button.png", 840, 285, renderer) );
    exitGameBtn_->setScale(buttonXScale, buttonYScale);
}

void TitleScreenUXLayer::render(SDL_Renderer* renderer) {
    mainPanel_->render(renderer);
    startGameBtn_->render(renderer);
    exitGameBtn_->render(renderer);
}

void TitleScreenUXLayer::updateMouse(int const x, int const y) {
    startGameBtn_->updateButtonState(x, y);
    exitGameBtn_->updateButtonState(x, y);
}