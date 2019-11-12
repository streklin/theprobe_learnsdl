#ifndef SPRITELAYER
#define SPRITELAYER

#include <SDL.h>

#include <memory>
#include <vector>

#include "Sprite.h"
#include "IGraphicsLayer.h"

class SpriteLayer final : public IGraphicsLayer {
public:
    SpriteLayer();

    void addSprite(std::shared_ptr<Sprite> sprite);
    void render(SDL_Renderer* renderer) override;
    void updateMouse(int const x, int const y) override;

    void clearSprites();
private:
    std::vector<std::shared_ptr<Sprite>> sprites_;
};

#endif