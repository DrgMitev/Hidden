#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <iostream>
#include <fstream>

#include "Character.h"
#include "LoadedTexture.h"
#include "MappingTilling.h"
#include "Constants.h"
#include "ConstantParameters.h"
using namespace std;
bool checkCollision(SDL_Rect a, SDL_Rect b);

Tile::Tile(int currentX, int currentY, int currentTileType, int currentTileTeleportValue, ConstantParameters currentConstantParameters)
{
	SDL_Rect currenTilePrameters = currentConstantParameters.getTileDimensions();
	x = currentX;
	y = currentY;
	tileType = currentTileType;
	//Set current tile offsets
	mBox.x = x;
	mBox.y = y;

	//Set  current tile dimensions
	mBox.w = currenTilePrameters.w;
	mBox.h = currenTilePrameters.h;

	//Set current tile type
	mType = tileType;
	//Set current tile teleport value
	tileTeleportValue = currentTileTeleportValue;
}
	
void Tile::render(SDL_Rect& camera, LoadedTexture gTileTexture ,SDL_Renderer* gameRenderer, SDL_Rect* gTileClips)
{
	
	//Checks if the tile should be on screen
	if (checkCollision(camera, mBox))
	{
		
		//Show the tile
		
		gTileTexture.render(mBox.x - camera.x, mBox.y - camera.y ,gameRenderer, &gTileClips[mType]);
		
	}
	
}
//Returns current tile type
int Tile::getType()
{
	return mType;
}
//Returns current tile dimensions and location
SDL_Rect Tile::getBox()
{
	return mBox;
}
//Returns current tile teleport value
int Tile::getTileTeleportValue() 
{
	return tileTeleportValue;
}