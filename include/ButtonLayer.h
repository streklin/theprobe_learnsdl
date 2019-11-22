#ifndef BUTTONLAYER
#define BUTTONLAYER

#include <SDL.h>
#include <vector>

#include "Button.h"
#include "GraphicsLayer.h"

class ButtonLayer final : public GraphicsLayer {
public:
    ButtonLayer(SDL_Renderer* renderer);

    void render() override;

    void handleEvents(SDL_Event* e);
    void addButton(Button* button);

private:
    std::vector<Button*> buttons_;
};

#endif