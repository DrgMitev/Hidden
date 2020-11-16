#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <iostream>
#include <math.h>


//Custom libraries
#include "Character.h"
#include "Enemy.h"
#include "MappingTilling.h"
#include "Constants.h"
#include "ConstantParameters.h"
#include "Collectable.h"
using namespace std;
//Checker for collision between enemy and a tile
bool checkCollision(SDL_Rect a, SDL_Rect b);
//Checker if the enemy touches a wall
bool touchesWall(SDL_Rect box, Tile* tiles[]);
//Checker if the enemy steps on teleport tile
int touchesWall(SDL_Rect box, Tile* tiles[], const int TileType);

//Set current enemy position
void Enemy::setPosition(const int currentX, const int currentY, const int currentHeight, const int currentWidth)
{
	x = currentX;
	y = currentY;
	height = currentHeight;
	width = currentWidth;
	

}

//Return current enemy position
SDL_Rect Enemy::getDimensions()
{
	SDL_Rect enemyBox;
	enemyBox.x = x;
	enemyBox.y = y;
	enemyBox.h = height;
	enemyBox.w = width;
	return enemyBox;

}
void Enemy::setObjectClips(ConstantParameters currentPanelConstantParameters)
{

	SDL_Rect enemyTileParameters = currentPanelConstantParameters.getEnemyTileDimensions();
	SDL_Rect enemyParameters = currentPanelConstantParameters.getEnemyDimensions();
	
	objectClips[CHARACTER_BACKWARD_STEP_0].x = 0 + enemyTileParameters.w / 5;
	objectClips[CHARACTER_BACKWARD_STEP_0].y = 0 + enemyTileParameters.h /5 ;
	objectClips[CHARACTER_BACKWARD_STEP_0].w = enemyParameters.w;
	objectClips[CHARACTER_BACKWARD_STEP_0].h = enemyParameters.h;

	objectClips[CHARACTER_BACKWARD_STEP_1].x = enemyTileParameters.w * 1 + enemyTileParameters.w / 5;
	objectClips[CHARACTER_BACKWARD_STEP_1].y = 0 + enemyTileParameters.h / 5;
	objectClips[CHARACTER_BACKWARD_STEP_1].w = enemyParameters.w;
	objectClips[CHARACTER_BACKWARD_STEP_1].h = enemyParameters.h;

	objectClips[CHARACTER_BACKWARD_STEP_2].x = enemyTileParameters.w * 2 + enemyTileParameters.w / 5;
	objectClips[CHARACTER_BACKWARD_STEP_2].y = 0 + enemyTileParameters.h / 5;
	objectClips[CHARACTER_BACKWARD_STEP_2].w = enemyParameters.w;
	objectClips[CHARACTER_BACKWARD_STEP_2].h = enemyParameters.h;

	objectClips[CHARACTER_BACKWARD_STEP_3].x = enemyTileParameters.w * 3 + enemyTileParameters.w / 5;
	objectClips[CHARACTER_BACKWARD_STEP_3].y = 0 + enemyTileParameters.h / 5;
	objectClips[CHARACTER_BACKWARD_STEP_3].w = enemyParameters.w;
	objectClips[CHARACTER_BACKWARD_STEP_3].h = enemyParameters.h;

	objectClips[CHARACTER_FORWARD_STEP_0].x = 0 + enemyTileParameters.w / 5;
	objectClips[CHARACTER_FORWARD_STEP_0].y = enemyTileParameters.h + enemyTileParameters.h / 5;
	objectClips[CHARACTER_FORWARD_STEP_0].w = enemyParameters.w;
	objectClips[CHARACTER_FORWARD_STEP_0].h = enemyParameters.h;

	objectClips[CHARACTER_FORWARD_STEP_1].x = enemyTileParameters.w * 1 + enemyTileParameters.w / 5;
	objectClips[CHARACTER_FORWARD_STEP_1].y = enemyTileParameters.h + enemyTileParameters.h / 5;
	objectClips[CHARACTER_FORWARD_STEP_1].w = enemyParameters.w;
	objectClips[CHARACTER_FORWARD_STEP_1].h = enemyParameters.h;

	objectClips[CHARACTER_FORWARD_STEP_2].x = enemyTileParameters.w * 2 + enemyTileParameters.w / 5;
	objectClips[CHARACTER_FORWARD_STEP_2].y = enemyTileParameters.h + enemyTileParameters.h / 5;
	objectClips[CHARACTER_FORWARD_STEP_2].w = enemyParameters.w;
	objectClips[CHARACTER_FORWARD_STEP_2].h = enemyParameters.h;

	objectClips[CHARACTER_FORWARD_STEP_3].x = enemyTileParameters.w * 3 + enemyTileParameters.w / 5;
	objectClips[CHARACTER_FORWARD_STEP_3].y = enemyTileParameters.h + enemyTileParameters.h / 5;
	objectClips[CHARACTER_FORWARD_STEP_3].w = enemyParameters.w;
	objectClips[CHARACTER_FORWARD_STEP_3].h = enemyParameters.h;

	objectClips[CHARACTER_RIGHTWARD_STEP_0].x = 0 + enemyTileParameters.w / 5;
	objectClips[CHARACTER_RIGHTWARD_STEP_0].y = enemyTileParameters.h*2 + enemyTileParameters.h / 5;
	objectClips[CHARACTER_RIGHTWARD_STEP_0].w = enemyParameters.w;
	objectClips[CHARACTER_RIGHTWARD_STEP_0].h = enemyParameters.h;

	objectClips[CHARACTER_RIGHTWARD_STEP_1].x = enemyTileParameters.w * 1 + enemyTileParameters.w / 5;
	objectClips[CHARACTER_RIGHTWARD_STEP_1].y = enemyTileParameters.h * 2 + enemyTileParameters.h / 5;
	objectClips[CHARACTER_RIGHTWARD_STEP_1].w = enemyParameters.w;
	objectClips[CHARACTER_RIGHTWARD_STEP_1].h = enemyParameters.h;

	objectClips[CHARACTER_RIGHTWARD_STEP_2].x = enemyTileParameters.w * 2 + enemyTileParameters.w / 5;
	objectClips[CHARACTER_RIGHTWARD_STEP_2].y = enemyTileParameters.h * 2 + enemyTileParameters.h / 5;
	objectClips[CHARACTER_RIGHTWARD_STEP_2].w = enemyParameters.w;
	objectClips[CHARACTER_RIGHTWARD_STEP_2].h = enemyParameters.h;

	objectClips[CHARACTER_RIGHTWARD_STEP_3].x = enemyTileParameters.w * 3 + enemyTileParameters.w / 5;
	objectClips[CHARACTER_RIGHTWARD_STEP_3].y = enemyTileParameters.h * 2 + enemyTileParameters.h / 5;
	objectClips[CHARACTER_RIGHTWARD_STEP_3].w = enemyParameters.w;
	objectClips[CHARACTER_RIGHTWARD_STEP_3].h = enemyParameters.h;


	objectClips[CHARACTER_LEFTWARD_STEP_0].x = 0 + enemyTileParameters.w / 5;
	objectClips[CHARACTER_LEFTWARD_STEP_0].y = enemyTileParameters.h * 3 + enemyTileParameters.h / 5;
	objectClips[CHARACTER_LEFTWARD_STEP_0].w = enemyParameters.w;								   
	objectClips[CHARACTER_LEFTWARD_STEP_0].h = enemyParameters.h;								   
																								   
	objectClips[CHARACTER_LEFTWARD_STEP_1].x = enemyTileParameters.w * 1 + enemyTileParameters.w / 5;
	objectClips[CHARACTER_LEFTWARD_STEP_1].y = enemyTileParameters.h * 3 + enemyTileParameters.h / 5;
	objectClips[CHARACTER_LEFTWARD_STEP_1].w = enemyParameters.w;								   
	objectClips[CHARACTER_LEFTWARD_STEP_1].h = enemyParameters.h;								   
																								   
	objectClips[CHARACTER_LEFTWARD_STEP_2].x = enemyTileParameters.w * 2 + enemyTileParameters.w / 5;
	objectClips[CHARACTER_LEFTWARD_STEP_2].y = enemyTileParameters.h * 3 + enemyTileParameters.h / 5;
	objectClips[CHARACTER_LEFTWARD_STEP_2].w = enemyParameters.w;								   
	objectClips[CHARACTER_LEFTWARD_STEP_2].h = enemyParameters.h;								   
																								   
	objectClips[CHARACTER_LEFTWARD_STEP_3].x = enemyTileParameters.w * 3 + enemyTileParameters.w / 5;
	objectClips[CHARACTER_LEFTWARD_STEP_3].y = enemyTileParameters.h * 3 + enemyTileParameters.h / 5;
	objectClips[CHARACTER_LEFTWARD_STEP_3].w = enemyParameters.w;
	objectClips[CHARACTER_LEFTWARD_STEP_3].h = enemyParameters.h;

	
}
void Enemy::setTexture(LoadedTexture currentTexture)
{
	texture = currentTexture;
}
//Displays the character on the screen
void Enemy::Render(SDL_Rect currentLevelCamera, SDL_Renderer* gameRenderer)

{
	//Displays the enemy on the screen
		//Renders the movable objects
		texture.render(x, y - currentLevelCamera.y, gameRenderer, &objectClips[renderState]);

	

}

//Changes current enemy position
void Enemy::Move(Character currentCharacter, Tile* tileSet[], ConstantParameters currentConstantParameters, int xOffset, int yOffset)
{
	//Resolution-dependent parameters
	SDL_Rect currentLevel = currentConstantParameters.getLevelDimensions();




	//Structured parameter for the current enemy 
	SDL_Rect characterBox = currentCharacter.getDimensions(); 
	
	SDL_Rect enemyBox;
	enemyBox.x = x;
	enemyBox.y = y;
	enemyBox.h = height;
	enemyBox.w = width;


	int distanceDiagonal = sqrt(pow((enemyBox.x + enemyBox.w) - (characterBox.x + characterBox.w), 2) + pow((enemyBox.y + enemyBox.h) - (characterBox.y + characterBox.h), 2));
	//Move if in range
	if (distanceDiagonal < 300)
	{
		//Set current state of enemy to "chase"
		state = chase;
	}
	else 
	{
		state = idle;
	}






	if(state == chase)
	{
		//Move rightwards
		if ((enemyBox.x + enemyBox.w) - (characterBox.x + characterBox.w) <= 0) 
		{

			enemyBox.x++;
			x++;
			//Checks if the enemy is out of bounds
			if (x > currentLevel.w - enemyBox.w - xOffset || touchesWall(enemyBox, tileSet))
			{
				enemyBox.x--;
				x--;
			}
			else if (renderState < CHARACTER_RIGHTWARD_STEP_0 || renderState > CHARACTER_RIGHTWARD_STEP_3)
			{
				renderState = CHARACTER_RIGHTWARD_STEP_0;
			}
			else if (renderState >= CHARACTER_RIGHTWARD_STEP_0 && renderState < CHARACTER_RIGHTWARD_STEP_3)
			{
				renderState ++;
			}
			else
			{
				renderState = CHARACTER_RIGHTWARD_STEP_0;
			}

		}
		//Move leftwards
		else if ((enemyBox.x + enemyBox.w) - (characterBox.x + characterBox.w) >= 0)
		{

			enemyBox.x--;
			x--;
			//Checks if the enemy is out of bounds
			if (x < 0 + xOffset || touchesWall(enemyBox, tileSet))
			{
				enemyBox.x++;
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

		}
		
		//Move backwards
		if ((enemyBox.y + enemyBox.h) - (characterBox.y + characterBox.h) <= 0) 
		{
			enemyBox.y++;
			y++;
			//Checks if the enemy is out of bounds
			if (y > currentLevel.h - enemyBox.h - yOffset || touchesWall(enemyBox, tileSet))
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
		}
		//Move forwards
		else if ((enemyBox.y + enemyBox.h) - (characterBox.y + characterBox.h) >= 0)
		{
			enemyBox.y--;
			y--;
			//Checks if the enemy is out of bounds
			if (y <0 + yOffset || touchesWall(enemyBox, tileSet))
			{
				enemyBox.y++;
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
		}
	
	}








}
//Teleports the enemy to a different location
void Enemy::Teleport(ConstantParameters currentConstantParameters)
{
	SDL_Rect currentEnemyParameters = currentConstantParameters.getCharacterDimensions();
	SDL_Rect currentTileParameters = currentConstantParameters.getTileDimensions();


	
	//Checks the enemy teleport destination
	if (teleportValue == TELEPORT_PRESET_1)
	{
		setPosition(int(currentTileParameters.w*23.5), int(currentTileParameters.h*1.5), currentEnemyParameters.h, currentEnemyParameters.w);

	}
	//Checks the enemy teleport destination
	if (teleportValue == TELEPORT_PRESET_2)
	{
		setPosition(int(currentTileParameters.w*23.5), int(currentTileParameters.h*21.5), currentEnemyParameters.h, currentEnemyParameters.w);

	}
	teleportRecalled = 0;
	teleportFinished = 1;
	teleportStarted = 0;
	
	

	
}



//Returns the current teleport state - Recalled or not 
int Enemy::getTeleportState()
{
	return teleportRecalled;
}
//Returns if the current teleport started
int Enemy::getTeleportStarted()
{
	return teleportStarted;
}
//Returns if the current teleport finished
int Enemy::getTeleportFinished() {
	return teleportFinished;
}
//Returns the current teleport destination of the enemy 
int Enemy::getTeleportValue() {
	return teleportValue;
}

//Set current teleport start
void Enemy::setTeleportStarted( int started) 
{
	teleportStarted = started;
}

//Set current teleport finish
void Enemy::setTeleportFinished(int finished ) 
{
	teleportFinished = finished;
}
//Set current teleport destination
void Enemy::setTeleportValue(int value)
{
	teleportValue = value;
}

void Enemy::setState(int value)
{
	state = value;
}