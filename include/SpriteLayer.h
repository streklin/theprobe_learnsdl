#ifndef SPRITELAYER
#define SPRITELAYER

#include <SDL.h>
#include <vector>

#include "GraphicsLayer.h"
#include "Sprite.h"

class SpriteLayer final : public GraphicsLayer {
public:
    SpriteLayer(SDL_Renderer* renderer);

    void render() override;
    void addSprite(Sprite* texture);
    void clearSprites();

    void update(const int elapsedTime);

private:
    std::vector<Sprite*> sprites_;
};

#endif