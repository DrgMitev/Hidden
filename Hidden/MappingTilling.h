#pragma once
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <iostream>
#include <fstream>


#include "Character.h"
#include "LoadedTexture.h"
#include "Constants.h"
#include "ConstantParameters.h"
using namespace std;
class Tile
{
public:
	//Initializes position and type
	Tile(int currentX, int currentY, int currentTileType, int currentTileTeleportValue, ConstantParameters currentConstantParameters);

	//Shows the tile
	void render(SDL_Rect& camera, LoadedTexture gTileTexture ,SDL_Renderer* gameRenderer, SDL_Rect gTileClips[]);

	//Returns the current tile type
	int getType();

	//Returns the current tile dimensions and location
	SDL_Rect getBox();
	//Returns the current tile teleport value
	int getTileTeleportValue();
private:
	//Current tile horizontal location
	int x;
	//Current tile vertical location
	int y;
	//Current tile type
	int tileType;
	//Current tile teleport value
	int tileTeleportValue;
	//The attributes of the tile
	SDL_Rect mBox;

	//The tile type
	int mType;
}; 
