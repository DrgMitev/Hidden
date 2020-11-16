#pragma once
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <iostream>
#include <fstream>

#include "MappingTilling.h"
#include "ConstantParameters.h"
using namespace std;
class Character
{
private:
	//Current character horizontal location
	int x;
	//Current character vertical location
	int y;
	//Current character width
	int width;
	//Current character geight
	int height;
	//Current character teleport state
	int teleportRecalled = 0 ;
	//If current character teleport started
	int teleportStarted = 0 ;
	//If current character teleport finished
	int teleportFinished = 0;
	//Current character teleport destination
	int teleportValue = 0;
	//Character living state
	int state = -1;
	//Character life
	int life = 3;
	//Enemy texture render state 
	int renderState = 0;
	SDL_Rect objectClips[TOTAL_OBJECT_SPRITES];

	LoadedTexture texture; 
public:
	//current character attributes
	Character() {};
	Character(const int currentX , const int currentY, const int currentHeight, const int currentWidth) 
	{
		x = currentX;
		y = currentY;
		width = currentHeight;
		height = currentWidth;
		

	}
	//Changes current character position
	void Move(string destination, Tile* tileSet[], ConstantParameters currentConstantParameters,int  xOffset, int yOffset);

	//Displays the character on the screen
	void Render(SDL_Rect currentLevelCamera, SDL_Renderer* gameRenderer);
	//Sets current character position
	void setPosition(const int x, const int y, const int currentHeight, const int currentWidth);

	//Return current character position
	SDL_Rect getDimensions();
	//Set character render clips
	void setObjectClips(ConstantParameters currentPanelConstantParameters);
	//Set character texture 
	void setTexture(LoadedTexture currentTexture);

	//Teleports the character to a different location
	void Teleport(ConstantParameters currentConstantParameters);
	//Returns the current teleport state - Recalled or not 
	int getTeleportState();
	//Returns if the current teleport started
	int getTeleportStarted();
	//Returns if the current teleport finished
	int getTeleportFinished();
	//Returns the current teleport destination of the character 
	int getTeleportValue();
	//Set current teleport start
	void setTeleportStarted(int started);
	//Set current teleport finish
	void setTeleportFinished(int finished);
	//Set current teleport destination
	void setTeleportValue(int value);
	//Set living state 
	void setState(int value);
	//Get living state 
	int getState();
	//Set life 
	void setLife(int currentLifeDegrader);
	//Get current life 
	int getLife();

};