#pragma once
#include <SDL.h>

#include "Character.h"
using namespace std;

class Collectable 
{
	private:
		//Stores the collectable dimensions
		SDL_Rect dimensions;
		//Stores collectable type
		int type;
		//If it has been scored
		bool collectableScored = false ;

	public: 
		//Setter
		Collectable() {};
		//Setter with properties
		Collectable(int x, int y, int w, int h, int type);
		//Checks if it has been scored, and set it if has been
		bool Checked(Character currentCharacter);
		//Returns if it has been scored
		bool Scored();
		//Renders the collectable
		void Render(SDL_Renderer* currentRenderer, SDL_Rect currentLevelCamera);
		//Returns the type of the collectable
		int Type();
};