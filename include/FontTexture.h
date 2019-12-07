#ifndef FONTTEXTURE
#define FONTTEXTURE

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Texture.h"

class FontTexture final : public Texture {
public:
    FontTexture(const std::string text, SDL_Renderer* renderer, TTF_Font* font);
    void createTextureFromText(const std::string text, SDL_Renderer* renderer, TTF_Font* font);
private:
    TTF_Font* font_; // non-owning data handle
    std::string text_;
    SDL_Color textColor_ = { 255, 255, 255 };
};

#endif