#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <iostream>



//Custom libraries
#include "Character.h"
#include "MappingTilling.h"
#include "Constants.h"
#include "ConstantParameters.h"
#include "Collectable.h"
using namespace std;
//Checker for collision between 2 boxes
bool checkCollision(SDL_Rect a, SDL_Rect b);
//Checker if the character touches a wall
bool touchesWall(SDL_Rect box, Tile* tiles[]);
//Checker if the character steps on teleport tile
int touchesWall(SDL_Rect box, Tile* tiles[], const int TileType);

//Set current character position
void Character::setPosition(const int currentX, const int currentY, const int currentHeight, const int currentWidth)
{
	x = currentX;
	y = currentY;
	height = currentHeight;
	width = currentWidth;
	

}

//Return current character position
SDL_Rect Character::getDimensions()
{
	SDL_Rect characterBox;
	characterBox.x = x;
	characterBox.y = y;
	characterBox.h = height;
	characterBox.w = width;
	return characterBox;

}
void Character::setObjectClips(ConstantParameters currentPanelConstantParameters)
{

	SDL_Rect characterTileParameters = currentPanelConstantParameters.getCharacterTileDimensions();
	SDL_Rect characterParameters = currentPanelConstantParameters.getCharacterDimensions();

	objectClips[CHARACTER_FORWARD_STEP_0].x = 0 + characterTileParameters.w / 3;
	objectClips[CHARACTER_FORWARD_STEP_0].y = 0 + characterTileParameters.h / 3;
	objectClips[CHARACTER_FORWARD_STEP_0].w = characterParameters.w ;
	objectClips[CHARACTER_FORWARD_STEP_0].h = characterParameters.h ;
	b
	objectClips[CHARACTER_FORWARD_STEP_1].x = 0 + characterTileParameters.w / 3;
	objectClips[CHARACTER_FORWARD_STEP_1].y = characterTileParameters.h + characterTileParameters.h / 3;
	objectClips[CHARACTER_FORWARD_STEP_1].w = characterParameters.w;
	objectClips[CHARACTER_FORWARD_STEP_1].h = characterParameters.h;

	objectClips[CHARACTER_FORWARD_STEP_2].x = 0 + characterTileParameters.w / 3;
	objectClips[CHARACTER_FORWARD_STEP_2].y = characterTileParameters.h * 2 + characterTileParameters.h / 3;
	objectClips[CHARACTER_FORWARD_STEP_2].w = characterParameters.w;
	objectClips[CHARACTER_FORWARD_STEP_2].h = characterParameters.h;

	objectClips[CHARACTER_FORWARD_STEP_3].x = 0 + characterTileParameters.w / 3;
	objectClips[CHARACTER_FORWARD_STEP_3].y = characterTileParameters.h * 3 + characterTileParameters.h / 3;
	objectClips[CHARACTER_FORWARD_STEP_3].w = characterParameters.w;
	objectClips[CHARACTER_FORWARD_STEP_3].h = characterParameters.h;

	objectClips[CHARACTER_LEFTWARD_STEP_0].x = characterTileParameters.w * 5 + characterTileParameters.w / 3;
	objectClips[CHARACTER_LEFTWARD_STEP_0].y = 0 + characterTileParameters.h / 3;
	objectClips[CHARACTER_LEFTWARD_STEP_0].w = characterParameters.w;
	objectClips[CHARACTER_LEFTWARD_STEP_0].h = characterParameters.h;

	objectClips[CHARACTER_LEFTWARD_STEP_1].x = characterTileParameters.w * 5 + characterTileParameters.w / 3;
	objectClips[CHARACTER_LEFTWARD_STEP_1].y = characterTileParameters.h + characterTileParameters.h / 3;
	objectClips[CHARACTER_LEFTWARD_STEP_1].w = characterParameters.w;
	objectClips[CHARACTER_LEFTWARD_STEP_1].h = characterParameters.h;

	objectClips[CHARACTER_LEFTWARD_STEP_2].x = characterTileParameters.w * 5 + characterTileParameters.w / 3;
	objectClips[CHARACTER_LEFTWARD_STEP_2].y = characterTileParameters.h * 2 + characterTileParameters.h / 3;
	objectClips[CHARACTER_LEFTWARD_STEP_2].w = characterParameters.w;
	objectClips[CHARACTER_LEFTWARD_STEP_2].h = characterParameters.h;

	objectClips[CHARACTER_LEFTWARD_STEP_3].x = characterTileParameters.w * 5 + characterTileParameters.w / 3;
	objectClips[CHARACTER_LEFTWARD_STEP_3].y = characterTileParameters.h * 3 + characterTileParameters.h / 3;
	objectClips[CHARACTER_LEFTWARD_STEP_3].w = characterParameters.w;
	objectClips[CHARACTER_LEFTWARD_STEP_3].h = characterParameters.h;

	objectClips[CHARACTER_BACKWARD_STEP_0].x = characterTileParameters.w * 4 + characterTileParameters.w / 3;
	objectClips[CHARACTER_BACKWARD_STEP_0].y = 0 + characterTileParameters.h / 3;
	objectClips[CHARACTER_BACKWARD_STEP_0].w = characterParameters.w;
	objectClips[CHARACTER_BACKWARD_STEP_0].h = characterParameters.h;

	objectClips[CHARACTER_BACKWARD_STEP_1].x = characterTileParameters.w * 4 + characterTileParameters.w / 3;
	objectClips[CHARACTER_BACKWARD_STEP_1].y = characterTileParameters.h + characterTileParameters.h / 3;
	objectClips[CHARACTER_BACKWARD_STEP_1].w = characterParameters.w;
	objectClips[CHARACTER_BACKWARD_STEP_1].h = characterParameters.h;

	objectClips[CHARACTER_BACKWARD_STEP_2].x = characterTileParameters.w * 4 + characterTileParameters.w / 3;
	objectClips[CHARACTER_BACKWARD_STEP_2].y = characterTileParameters.h * 2 + characterTileParameters.h / 3;
	objectClips[CHARACTER_BACKWARD_STEP_2].w = characterParameters.w;
	objectClips[CHARACTER_BACKWARD_STEP_2].h = characterParameters.h;

	objectClips[CHARACTER_BACKWARD_STEP_3].x = characterTileParameters.w * 4 + characterTileParameters.w / 3;
	objectClips[CHARACTER_BACKWARD_STEP_3].y = characterTileParameters.h * 3 + characterTileParameters.h / 3;
	objectClips[CHARACTER_BACKWARD_STEP_3].w = characterParameters.w;
	objectClips[CHARACTER_BACKWARD_STEP_3].h = characterParameters.h;

	objectClips[CHARACTER_RIGHTWARD_STEP_0].x =  characterTileParameters.w * 2 + characterTileParameters.w / 3;
	objectClips[CHARACTER_RIGHTWARD_STEP_0].y = 0 + characterTileParameters.h / 3;
	objectClips[CHARACTER_RIGHTWARD_STEP_0].w = characterParameters.w;
	objectClips[CHARACTER_RIGHTWARD_STEP_0].h = characterParameters.h;
											 
	objectClips[CHARACTER_RIGHTWARD_STEP_1].x =  characterTileParameters.w * 2 + characterTileParameters.w / 3;
	objectClips[CHARACTER_RIGHTWARD_STEP_1].y = characterTileParameters.h + characterTileParameters.h / 3;
	objectClips[CHARACTER_RIGHTWARD_STEP_1].w = characterParameters.w;
	objectClips[CHARACTER_RIGHTWARD_STEP_1].h = characterParameters.h;
											 
	objectClips[CHARACTER_RIGHTWARD_STEP_2].x =  characterTileParameters.w * 2 + characterTileParameters.w / 3;
	objectClips[CHARACTER_RIGHTWARD_STEP_2].y =  characterTileParameters.h * 2 + characterTileParameters.h / 3;
	objectClips[CHARACTER_RIGHTWARD_STEP_2].w = characterParameters.w;
	objectClips[CHARACTER_RIGHTWARD_STEP_2].h = characterParameters.h;
											 
	objectClips[CHARACTER_RIGHTWARD_STEP_3].x =  characterTileParameters.w * 2 + characterTileParameters.w / 3;
	objectClips[CHARACTER_RIGHTWARD_STEP_3].y =  characterTileParameters.h * 3 + characterTileParameters.h / 3;
	objectClips[CHARACTER_RIGHTWARD_STEP_3].w = characterParameters.w;
	objectClips[CHARACTER_RIGHTWARD_STEP_3].h = characterParameters.h;
}

void Character::setTexture(LoadedTexture currentTexture) {
	texture = currentTexture;
}

//Displays the character on the screen
void Character::Render(SDL_Rect currentLevelCamera,SDL_Renderer* gameRenderer)

{
	//Renders the movable objects
	texture.render(x, y - currentLevelCamera.y, gameRenderer, &objectClips[renderState]);

}

//Changes current character position
void Character::Move(string destination , Tile* tileSet[], ConstantParameters currentConstantParameters, int xOffset, int yOffset)
{
	//Resolution-dependent parameters
	SDL_Rect currentLevelDimensions = currentConstantParameters.getLevelDimensions();
	SDL_Rect currentCharacterDimensions = currentConstantParameters.getCharacterDimensions();

	//Structured parameter for the current character 
	SDL_Rect characterBox; 
	characterBox.x = x ;
	characterBox.y = y ;
	characterBox.h = height;
	characterBox.w = width;

	
	//Moving upwards
	if (destination == "up")
	{
		characterBox.y--;
		y--;
		//Checks if the character is out of bounds
		if (y <0 + yOffset  || touchesWall(characterBox , tileSet))
		{
			characterBox.y++;
			y++;
			
		}
		else if (renderState < CHARACTER_FORWARD_STEP_0 || renderState > CHARACTER_FORWARD_STEP_3)
		{
			renderState = CHARACTER_FORWARD_STEP_0;
		}
		else if (renderState >= CHARACTER_FORWARD_STEP_0 && renderState < CHARACTER_FORWARD_STEP_3)
		{
			renderState++;
		}
		else
		{
			renderState = CHARACTER_FORWARD_STEP_0;
		}
		//Checks if the character steps on a teleport tile
		int tileTeleportValue = touchesWall(characterBox, tileSet, TILE_TELEPORT_START);
		if ( tileTeleportValue != 0 ) 
		{	

			teleportRecalled = 1;
			teleportValue = tileTeleportValue;
		}
		

	}
	//Moving downwards
	else if (destination == "down")
	{
		characterBox.y++;
		y++;
		//Checks if the character is out of bounds
		if (y > currentLevelDimensions.h-currentCharacterDimensions.h - yOffset || touchesWall(characterBox, tileSet) )
		{
			characterBox.y--;
			y--;
		}
		else if (renderState < CHARACTER_BACKWARD_STEP_0 || renderState > CHARACTER_BACKWARD_STEP_3)
		{
			renderState = CHARACTER_BACKWARD_STEP_0;
		}
		else if (renderState >= CHARACTER_BACKWARD_STEP_0 && renderState < CHARACTER_BACKWARD_STEP_3)
		{
			renderState++;
		}
		else
		{
			renderState = CHARACTER_BACKWARD_STEP_0;
		}
		//Checks if the character steps on a teleport tile
		int tileTeleportValue = touchesWall(characterBox, tileSet, TILE_TELEPORT_START);
		if (tileTeleportValue != 0)
		{

			teleportRecalled = 1;
			teleportValue = tileTeleportValue;
		}
		

	}
	//Moving rightwards
	else if (destination == "right")
	{
		characterBox.x++;
		x++;
		//Checks if the character is out of bounds
		if (x > currentLevelDimensions.w-currentCharacterDimensions.w  - xOffset|| touchesWall(characterBox, tileSet))
		{
			characterBox.x--;
			x--;
		}
		else if (renderState < CHARACTER_RIGHTWARD_STEP_0 || renderState > CHARACTER_RIGHTWARD_STEP_3)
		{
			renderState = CHARACTER_RIGHTWARD_STEP_0;
		}
		else if (renderState >= CHARACTER_RIGHTWARD_STEP_0 && renderState < CHARACTER_RIGHTWARD_STEP_3)
		{
			renderState++;
		}
		else
		{
			renderState = CHARACTER_RIGHTWARD_STEP_0;
		}
		//Checks if the character steps on a teleport tile
		int tileTeleportValue = touchesWall(characterBox, tileSet, TILE_TELEPORT_START);
		if (tileTeleportValue != 0)
		{

			teleportRecalled = 1;
			teleportValue = tileTeleportValue;
		}
		

	}
	//Moving leftwards
	else if (destination == "left")
	{
		characterBox.x--;
		x--;
		//Checks if the character is out of bounds
		if (x < 0 + xOffset || touchesWall(characterBox, tileSet))
		{
			characterBox.x++;
			x++;
		}
		else if (renderState < CHARACTER_LEFTWARD_STEP_0 || renderState > CHARACTER_LEFTWARD_STEP_3)
		{
			renderState = CHARACTER_LEFTWARD_STEP_0;
		}
		else if (renderState >= CHARACTER_LEFTWARD_STEP_0 && renderState < CHARACTER_LEFTWARD_STEP_3)
		{
			renderState++;
		}
		else
		{
			renderState = CHARACTER_LEFTWARD_STEP_0;
		}
		//Checks if the character steps on a teleport tile
		int tileTeleportValue = touchesWall(characterBox, tileSet, TILE_TELEPORT_START);
		if (tileTeleportValue != 0)
		{

			teleportRecalled = 1;
			teleportValue = tileTeleportValue;
		}
		

	}
	//Nothing has changed 
	else if (destination == "nowhere" )
	{
		x = x; 
		y = y;
	}
	//Checks if the character steps on a teleport tile
	
	if (touchesWall(characterBox, tileSet, TILE_TELEPORT_START) != 0 )
	{
		int tileTeleportValue = touchesWall(characterBox, tileSet, TILE_TELEPORT_START);
		teleportRecalled = 1;
		teleportValue = tileTeleportValue;
	}
	else if (touchesWall(characterBox, tileSet, TILE_TELEPORT_FINISH) != 0)
	{
		int tileTeleportValue = touchesWall(characterBox, tileSet, TILE_TELEPORT_FINISH);
		teleportRecalled = 1;
		teleportValue = tileTeleportValue;
	}
}
//Teleports the character to a different location
void Character::Teleport(ConstantParameters currentConstantParameters)
{
	SDL_Rect currentCharacterParameters = currentConstantParameters.getCharacterDimensions();
	SDL_Rect currentTileParameters = currentConstantParameters.getTileDimensions();


	
	//Checks the character teleport destination
	if (teleportValue == TELEPORT_PRESET_1)
	{
		setPosition(int(currentTileParameters.w*23.5), int(currentTileParameters.h*21.5), currentCharacterParameters.h, currentCharacterParameters.w);

	}
	//Checks the character teleport destination
	if (teleportValue == TELEPORT_PRESET_2)
	{
		setPosition(int(currentTileParameters.w*10.5), int(currentTileParameters.h*4.5), currentCharacterParameters.h, currentCharacterParameters.w);

	}
	teleportRecalled = 0;
	teleportFinished = 1;
	teleportStarted = 0;
	
	

	
}



//Returns the current teleport state - Recalled or not 
int Character::getTeleportState()
{
	return teleportRecalled;
}
//Returns if the current teleport started
int Character::getTeleportStarted()
{
	return teleportStarted;
}
//Returns if the current teleport finished
int Character::getTeleportFinished() {
	return teleportFinished;
}
//Returns the current teleport destination of the character 
int Character::getTeleportValue() {
	return teleportValue;
}

//Set current teleport start
void Character::setTeleportStarted( int started) 
{
	teleportStarted = started;
}

//Set current teleport finish
void Character::setTeleportFinished(int finished ) 
{
	teleportFinished = finished;
}
//Set current teleport destination
void Character::setTeleportValue(int value)
{
	teleportValue = value;
}

void Character::setState(int value)
{
	state = value;
}
int  Character::getState()
{
	return state;
}

void Character :: setLife(int currentLife) {
	life -= currentLife;
}
int Character::getLife() {
	return life;
}