#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <iostream>
#include <SDL_TTF.h>

#include "ConstantParameters.h"
#include "Constants.h"

using namespace std;

ConstantParameters::ConstantParameters(SDL_DisplayMode curentScreenDimensions)
{
	if (curentScreenDimensions.h < 1080 && curentScreenDimensions.w < 1920)
		{
			screen.w = 1280;
			screen.h = 720;

			level.w = 1280;
			level.h = 1440;

			tile.w = 53;
			tile.h = 53; 
			
			button.w = 179;
			button.h = 55;

			scoreboardBackground.w = 951;
			scoreboardBackground.h = 82;
			
			characterTile.w = 66;
			characterTile.h = 66;
			
			character.w = characterTile.w / 3;
			character.h = characterTile.h / 3;

			enemyTile.w = 33;
			enemyTile.h = 33;

			enemy.w = enemyTile.w / 1.5;
			enemy.h = enemyTile.h / 1.5;


		}
	else 
	{
		screen.w = 1920;
		screen.h = 1080;

		level.w = 1920;
		level.h = 2160;

		tile.w = 80;
		tile.h = 80;

		button.w = 268;
		button.h = 83;

		scoreboardBackground.w = 1473;
		scoreboardBackground.h = 123;

		characterTile.w = 148;
		characterTile.h = 148;

		character.w = characterTile.w / 3;
		character.h = characterTile.h / 3;


		enemyTile.w = 50;
		enemyTile.h = 50;

		enemy.w = enemyTile.w/1.5  ;
		enemy.h = enemyTile.h/1.5 ;



	}

}

SDL_Rect ConstantParameters::getScreenDimensions() {
	return screen;
}

SDL_Rect ConstantParameters::getLevelDimensions() {
	return level;
}

SDL_Rect ConstantParameters::getCharacterDimensions() {
	return character;
}

SDL_Rect ConstantParameters::getEnemyDimensions() {
	return enemy;
}

SDL_Rect ConstantParameters::getTileDimensions() {
	return tile;
}

SDL_Rect ConstantParameters::getButtonDimensions() {
	return button;
}

SDL_Rect ConstantParameters::getScoreboardBackgroundDimensions() {
	return scoreboardBackground;
}

SDL_Rect ConstantParameters::getCharacterTileDimensions() {
	return characterTile;
}

SDL_Rect ConstantParameters::getEnemyTileDimensions() {
	return enemyTile;
}




