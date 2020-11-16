#pragma once
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <iostream>
#include <SDL_TTF.h>

class ConstantParameters
{
public:
	//Empty setter 
	ConstantParameters() {};
	//Resolution-dependent setter of the parameters
	ConstantParameters(SDL_DisplayMode curentScreenDimensions);
	//Returns setted current screen dimensions
	SDL_Rect getScreenDimensions();
	//Returns setted level sizes relatively to the current screen resolution
	SDL_Rect getLevelDimensions();
	//Returns character size relatively to the current screen resolution
	SDL_Rect getCharacterDimensions();
	//Returns enemy size relatively to the current screen resolution
	SDL_Rect getEnemyDimensions();
	//Returns tiles size relatively to the current screen resolution
	SDL_Rect getTileDimensions();
	//Returns buttons size relatively to the current screen resolution
	SDL_Rect getButtonDimensions();
	//Returns scoreboard background size relatively to the current screen resolution
	SDL_Rect getScoreboardBackgroundDimensions();
	//Returns character tile size relatively to the current screen resolution
	SDL_Rect getCharacterTileDimensions();
	//Returns enemy tile size relatively to the current screen resolution
	SDL_Rect getEnemyTileDimensions();

private:
	//Stores setted current screen dimensions
	SDL_Rect screen; 
	//Stores setted level sizes relatively to the current screen resolution
	SDL_Rect level;
	//Stores character size relatively to the current screen resolution
	SDL_Rect character;
	//Stores enemy size relatively to the current screen resolution
	SDL_Rect enemy;
	//Stores tiles size relatively to the current screen resolution
	SDL_Rect tile;
	//Stores buttons size relatively to the current screen resolution
	SDL_Rect button;
	//Stores scoreboard background size relatively to the current screen resolution
	SDL_Rect scoreboardBackground;
	//Stores character tiles size relatively to the current screen resolution
	SDL_Rect characterTile;
	//Stores enemy tiles size relatively to the current screen resolution
	SDL_Rect enemyTile;


};
