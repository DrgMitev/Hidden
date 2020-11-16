#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <iostream>
#include <fstream>
#include <SDL_ttf.h>
#include "LoadedTexture.h"
#include "Constants.h"
using namespace std;
//Taken and modified from lazyfoo.net
LoadedTexture::LoadedTexture()
{
	//Creates blank texture 
	finishedTexture = NULL;
	textureWidth = 0;
	textureHeight = 0;
	texturePixels = NULL;
	texturePitch = 0;
}
//Destroy loaded texture 
LoadedTexture::~LoadedTexture()
{
	if (ProgramIsFinished)
	{
		ClearTexture();
	}
	//Deallocate
	
}
//Loads the texture from image at specified path
bool LoadedTexture::loadFromFile(string currentPath, SDL_Renderer* gameRenderer)
{
	//Clear preloaded texture
	ClearTexture();

	//Texture to be stored
	SDL_Texture* newTexture = NULL;

	//Loaded image at location
	SDL_Surface* loadedSurface = IMG_Load(currentPath.c_str());
	if (loadedSurface == NULL)
	{
		cout << ("Unable to load image %s! SDL_image Error ID: %s\n", currentPath.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to display format
		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_PIXELFORMAT_RGBA8888, NULL);
		if (formattedSurface == NULL)
		{
			cout << ("Unable to convert loaded surface to display format! %s\n", SDL_GetError());
		}
		else
		{
			//Create blank streamable texture
			newTexture = SDL_CreateTexture(gameRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, formattedSurface->w, formattedSurface->h);
			if (newTexture == NULL)
			{
				cout << ("Unable to create blank texture! SDL Error: %s\n", SDL_GetError());
			}
			else
			{
				//Enable blending on texture
				SDL_SetTextureBlendMode(newTexture, SDL_BLENDMODE_BLEND);

				//Lock texture for manipulation
				SDL_LockTexture(newTexture, &formattedSurface->clip_rect, &texturePixels, &texturePitch);

				//Copy loaded/formatted surface pixels
				memcpy(texturePixels, formattedSurface->pixels, formattedSurface->pitch * formattedSurface->h);

				//Get image dimensions
				textureWidth = formattedSurface->w;
				textureHeight = formattedSurface->h;

				//Get pixel data in editable format
				Uint32* pixels = (Uint32*)texturePixels;
				int pixelCount = (texturePitch / 4) * textureHeight;


				//Doesn't work with the release build
				//Map colors				
				Uint32 colorKey = SDL_MapRGB(formattedSurface->format, 0, 0xFF, 0xFF);
				Uint32 transparent = SDL_MapRGBA(formattedSurface->format, 0, 0xFF, 0xFF, 0);

				//Color key pixels
				for (int i = 0; i < pixelCount; ++i)
				{
					if (pixels[i] == colorKey)
					{
						pixels[i] = transparent;
					}
				}

				//Unlock texture to update
				SDL_UnlockTexture(newTexture);
				texturePixels = NULL;
			}

			//Clear mem of formatted Surface
			SDL_FreeSurface(formattedSurface);
		}

		//Clear mem of loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	finishedTexture = newTexture;
	return finishedTexture != NULL;
}

#ifdef _SDL_TTF_H
//Loads the texture from string text 
bool LoadedTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor,TTF_Font* gFont, SDL_Renderer* gameRenderer)
{
	//Clears preloaded texture
	ClearTexture();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		finishedTexture = SDL_CreateTextureFromSurface(gameRenderer, textSurface);
		if (finishedTexture == NULL)
		{
			cout << ("Unable to create texture from rendered text! SDL Error ID: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			textureWidth = textSurface->w;
			textureHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		cout << ("Unable to render text surface! SDL_ttf Error ID: %s\n", TTF_GetError());
	}


	//Return success
	return finishedTexture != NULL;
}
#endif


//Clear the loaded texture
void LoadedTexture::ClearTexture() {
	//Clear texture if it exists

	if (finishedTexture != NULL)
	{
		SDL_DestroyTexture(finishedTexture);
		finishedTexture = NULL;
		textureWidth = 0;
		textureHeight = 0;
		texturePixels = NULL;
		texturePitch = 0;
	}
}
//Set current color modulator 
void LoadedTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(finishedTexture, red, green, blue);
}
//Set current blend mode 
void LoadedTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(finishedTexture, blending);
}
//Set current alpha mode 
void LoadedTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(finishedTexture, alpha);
}
//Displays the texture to the screen
void LoadedTexture::render(int x, int y, SDL_Renderer* gameRenderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, textureWidth, textureHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gameRenderer, finishedTexture, clip, &renderQuad, angle, center, flip);

}
//Sets as a rendering premier target
void LoadedTexture::setAsRenderTarget(SDL_Renderer* gameRenderer)
{
	//Make self render target
	SDL_SetRenderTarget(gameRenderer, finishedTexture);
}
//Returns current texture width
int LoadedTexture::getWidth()
{
	return textureWidth;
}
//Returns current texture height
int LoadedTexture::getHeight()
{
	return textureHeight;
}
//Locks the texture for changes
bool LoadedTexture::lockTexture()
{
	bool success = true;

	//Texture is already locked
	if (texturePixels != NULL)
	{
		cout << ("Texture is already locked!\n");
		success = false;
	}
	//Lock texture
	else
	{
		if (SDL_LockTexture(finishedTexture, NULL, &texturePixels, &texturePitch) != 0)
		{
			cout << ("Unable to lock texture! %s\n", SDL_GetError());
			success = false;
		}
	}

	return success;
}
//Unlocks the texture for changes
bool LoadedTexture::unlockTexture()
{
	bool success = true;

	//Texture is not locked
	if (texturePixels == NULL)
	{
		cout << ("Texture is not locked!\n");
		success = false;
	}
	//Unlock texture
	else
	{
		SDL_UnlockTexture(finishedTexture);
		texturePixels = NULL;
		texturePitch = 0;
	}

	return success;
}
//Returns current texture pixels
void* LoadedTexture::getPixelsCount()
{
	return texturePixels;
}
//Copies the current texture pixels
void LoadedTexture::copyPixels(void* pixels)
{
	//Texture is locked
	if (texturePixels != NULL)
	{
		//Copy to locked pixels
		memcpy(texturePixels, pixels, texturePitch * textureHeight);
	}
}
//Returns current texture pitch
int LoadedTexture::getPitch()
{
	return texturePitch;
}

Uint32 LoadedTexture::getPixel32(unsigned int x, unsigned int y)
{
	//Convert the pixels to 32 bit
	Uint32 *pixels = (Uint32*)texturePixels;

	//Get the pixel requested
	return pixels[(y * (texturePitch / 4)) + x];
}
