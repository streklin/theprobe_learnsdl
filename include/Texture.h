#ifndef TEXTURE
#define TEXTURE

#include <string>
#include <SDL.h>

class Texture {
public:
    Texture();
    ~Texture();

    bool loadTexture(const std::string path, SDL_Renderer* renderer);
    SDL_Texture* getTexture();

    virtual void render(SDL_Renderer* renderer);

    int getWidth();
    int getHeight();

    void setScale(const float x, const float y);
    void setPosition(const int x, const int y);

    int getX() { return x_; }
    int getY() { return y_; }

protected:
    SDL_Texture* texture_;

    float xScale_;
    float yScale_;

    int x_;
    int y_;

    int width_;
    int height_;
};

#endif