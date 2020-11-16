#pragma once
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <iostream>
//Texture wrapper class
class LoadedTexture
{
public:
	//Create blank texture 
	LoadedTexture();

	//Clear texture memory
	~LoadedTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path, SDL_Renderer* gameRenderer);

#ifdef _SDL_TTF_H
	//Creates image from text string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* gFont, SDL_Renderer* gameRenderer);
#endif

	
	//Clear texture parameters and adress
	void ClearTexture();

	//Set color for color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending type
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation type
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y,  SDL_Renderer* gameRenderer, SDL_Rect* clip = NULL , double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Set self as render target
	void setAsRenderTarget(SDL_Renderer* gameRenderer);

	//Gets image dimensions
	int getWidth();
	int getHeight();

	//Pixel manipulators
	bool lockTexture();
	bool unlockTexture();
	void* getPixelsCount();
	void copyPixels(void* pixels);
	int getPitch();
	Uint32 getPixel32(unsigned int x, unsigned int y);

private:
	//The actual hardware texture
	SDL_Texture* finishedTexture;
	void* texturePixels;
	int texturePitch;

	//Image dimensions
	int textureWidth;
	int textureHeight;
};
