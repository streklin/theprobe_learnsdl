#ifndef TITLESCREENUXLAYER
#define TITLESCREENUXLAYER

#include <SDL.h>
#include <memory>
#include "Panel.h"
#include "Button.h"
#include "IGraphicsLayer.h"

class TitleScreenUXLayer final : public IGraphicsLayer {
public:
    TitleScreenUXLayer(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer) override;

    void updateMouse(int const x, int const y) override;

private:
    std::unique_ptr<Panel> mainPanel_;
    std::unique_ptr<Button> exitGameBtn_;
    std::unique_ptr<Button> startGameBtn_;
};

#endif