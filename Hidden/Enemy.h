#pragma once
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <iostream>
#include <fstream>

#include "MappingTilling.h"
#include "ConstantParameters.h"
using namespace std;
class Enemy
{
private:
	//Current enemy horizontal location
	int x;
	//Current enemy vertical location
	int y;
	//Current enemy width
	int width;
	//Current enemy geight
	int height;
	//Current enemy teleport state
	int teleportRecalled = 0 ;
	//If current enemy teleport started
	int teleportStarted = 0 ;
	//If current enemy teleport finished
	int teleportFinished = 0;
	//Current enemy teleport destination
	int teleportValue = 0;
	//Character living state
	int state = -1;
	//Enemy texture render state 
	int renderState = 0;
	//Stores enemy render clips
	SDL_Rect objectClips[TOTAL_OBJECT_SPRITES];
	//Stores enemy texture
	LoadedTexture texture;
public:
	//current enemy attributes
	Enemy() {};
	Enemy(const int currentX , const int currentY, const int currentHeight, const int currentWidth) 
	{
		x = currentX;
		y = currentY;
		width = currentHeight;
		height = currentWidth;
		

	}
	//Changes current enemy position
	void Move(Character currentCharacter, Tile* tileSet[], ConstantParameters currentConstantParameters, int xOffset, int yOffset);

	//Displays the enemy on the screen
	void Render(SDL_Rect currentLevelCamera, SDL_Renderer* gameRenderer);

	//Sets current enemy position
	void setPosition(const int x, const int y, const int currentHeight, const int currentWidth);

	//Return current enemy position
	SDL_Rect getDimensions();

	//Set enemy render clips
	void setObjectClips(ConstantParameters currentPanelConstantParameters);
	//Set texture to the structure
	void setTexture(LoadedTexture currentTexture);

	//Teleports the enemy to a different location
	void Teleport(ConstantParameters currentConstantParameters);
	//Returns the current teleport state - Recalled or not 
	int getTeleportState();
	//Returns if the current teleport started
	int getTeleportStarted();
	//Returns if the current teleport finished
	int getTeleportFinished();
	//Returns the current teleport destination of the enemy 
	int getTeleportValue();
	//Set current teleport start
	void setTeleportStarted(int started);
	//Set current teleport finish
	void setTeleportFinished(int finished);
	//Set current teleport destination
	void setTeleportValue(int value);
	//Set living state 
	void setState(int value);
};