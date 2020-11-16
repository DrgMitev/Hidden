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
//Checker for collision between 2 boxes
bool checkCollision(SDL_Rect a, SDL_Rect b);
//Checker if a dot touches a wall
bool touchesWall(SDL_Rect box, Tile* tiles[]);
//Checker if a dot steps on teleport tile
int touchesWall(SDL_Rect box, Tile* tiles[], const int TileType);


bool checkCollision(SDL_Rect a, SDL_Rect b)
{
	//The sides of the boxes
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Set the sides of box A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Set the sides of box B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}

bool touchesWall(SDL_Rect box, Tile* tiles[])
{
	//Goes through the tiles
	for (int i = 0; i < TOTAL_TILES; i++)
	{
		//If the tile is a wall type tile
		if ((tiles[i]->getType() >= TILE_CENTER) && (tiles[i]->getType() < TILE_FINISH) || (tiles[i]->getType() == TILE_QUADRUPLE_SIDED))
		{
			//If the collision box touches the wall tile
			if (checkCollision(box, tiles[i]->getBox()))
			{
				return true;
			}

		}
	}

	//If no wall tiles were touched
	return false;
}
int touchesWall(SDL_Rect box, Tile* tiles[], int tileType)
{
	//Goes through the tiles
	for (int i = 0; i < TOTAL_TILES; i++)
	{
		//If the tile is a teleport type tile
		if ((tiles[i]->getType() == tileType) && checkCollision(box, tiles[i]->getBox()))
		{
			return tiles[i]->getTileTeleportValue();

		}
	}

	//If no wall tiles were touched
	return false;
}