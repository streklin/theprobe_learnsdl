#ifndef TEXTURE
#define TEXTURE

#include <string>
#include <SDL.h>

class Texture {
public:
    Texture();

    bool loadTexture(const std::string path, SDL_Renderer* renderer);
    SDL_Texture* getTexture();

    virtual void render(SDL_Renderer* renderer);

    int getWidth();
    int getHeight();

    void setScale(const float x, const float y);

protected:
    float xScale_;
    float yScale_;
    
private:
    SDL_Texture* texture_;

    int width_;
    int height_;
};

#endif