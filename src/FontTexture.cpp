#include <SDL.h>
#include <SDL_ttf.h>
#include "FontTexture.h"

FontTexture::FontTexture(const std::string text, SDL_Renderer* renderer, TTF_Font* font) : Texture() {
    font_ = font;
    text_ = text;

    createTextureFromText(text, renderer, font);
}


 void FontTexture::createTextureFromText(const std::string text, SDL_Renderer* renderer, TTF_Font* font) {
  	SDL_Surface* textSurface = TTF_RenderText_Solid( font, text.c_str(), textColor_ );

	if( textSurface == NULL )
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        texture_ = SDL_CreateTextureFromSurface( renderer, textSurface );
		if( texture_ == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			width_ = textSurface->w;
			height_ = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	
 }

