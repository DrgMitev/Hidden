#include <SDL.h>

#include "Character.h"
#include "Collectable.h"

//Initializes basic collectables attributes
Collectable::Collectable(int currentX, int currentY, int currentW, int currentH, int currentType)
{
	dimensions ={ currentX, currentY, currentW, currentH };
	type = currentType;
}
bool Collectable::Checked(Character currentCollectable) {
	//Stores the collectable dimensions
	SDL_Rect collectableBox = currentCollectable.getDimensions();
	
	bool isChecked = true;
	//Check if top of the collectable doesn't overlapses bottom of the collectable
	if (dimensions.y >= collectableBox.y + collectableBox.h) {
		isChecked = false; 
	}
	//Check if bottom of the  doesn't collectable overlapses top of the collectable
	if (dimensions.y + dimensions.h <= collectableBox.y ) {
		isChecked = false;
	}
	//Check if left side of the  doesn't collectable overlapses right side  the collectable
	if (dimensions.x >= collectableBox.x + collectableBox.w) {	
		isChecked = false;
	}
	//Check if right side of the doesn't collectable overlapses left side  the collectable
	if (dimensions.x + dimensions.w <= collectableBox.x ) {
		isChecked = false;
	}
	//Check if it has been scored already
	if (isChecked) {
		collectableScored = true; 
	}
	return isChecked;
	
}
//Checks if the collectable has been scored
bool Collectable::Scored() {
	return collectableScored;
}
//Render the collectable
void Collectable::Render(SDL_Renderer* currentRenderer, SDL_Rect currentLevelCamera)
{
	SDL_SetRenderDrawColor(currentRenderer, 255, 255, 0, 0);
	//Loops to draw the collectable on the screen
	for (int collectableCurrentRenderedHeight = dimensions.y; collectableCurrentRenderedHeight <= dimensions.y + dimensions.h; collectableCurrentRenderedHeight++)
	{
		for (int collectableRenderedWidth = dimensions.x; collectableRenderedWidth <= dimensions.x + dimensions.w; collectableRenderedWidth++)
		{
			
			SDL_RenderDrawPoint(currentRenderer, collectableRenderedWidth, collectableCurrentRenderedHeight - currentLevelCamera.y);
		}
	}
}

int Collectable::Type(){
	return type;
}