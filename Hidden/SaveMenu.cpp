#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <SDL_mixer.h>
using namespace std;



//Custom libraries

#include "Constants.h"
#include "Character.h"
#include "LoadedTexture.h"
#include "MappingTilling.h"
#include "ConstantParameters.h"

//The window the window to be rendered to 
SDL_Window* saveMenuWindow = NULL;

//The window renderer
SDL_Renderer* saveMenuRenderer = NULL;

//Loaded text font and font color
TTF_Font* saveMenuFont;
//Loaded secondary  text font and font color
TTF_Font* saveMenuFontH2;
//Loaded font color
SDL_Color textColor = { 255,255,255 };
//Loaded steps of character text
LoadedTexture CongratulationsTextTexture;
//Loaded steps of character text
LoadedTexture CharacterStepsTexture;
//Loaded timer text
LoadedTexture TimerTexture;
//Loaded collectables text
LoadedTexture CollectablesTexture;






//Loads media
bool saveMenuMedia();
//Stores current player name
string  playerName = "";



//Loaded save button texture
LoadedTexture saveButtonTexture;
//Save button dimensions
SDL_Rect saveButton;
//Buttons clips for dinamic button texture
SDL_Rect saveButtonClips[3];
//Stores previously measured time of the program
int previousTicks = 0;
//Stores steps count
int characterCurrentSteps;
//Current character living state 
int characterState = 0;





//Stores string of the steps to be saved in DB/save file 
string characterStepsText;
//Stores string of the current timer to be saved in DB/save file 
string timerText;
//Stores string of the current collectables score to be saved in DB/save file 
string collectablesText;

//Save score
void saveScore(string playerName, int characterSteps, int timer, int collectablesScore, string gameState);
//Loaded winning sound
Mix_Chunk* winSound;

//Stores current panel parameters 
SDL_Rect saveMenuPanelButtonDimensions;
SDL_Rect saveMenuPanelScreenDimensions;
//Load textures for current panel
bool saveMenuMedia()
{
	//Loading success flag
	bool success = true;

	//Load 1280x720 resolution button texture
	if (saveMenuPanelScreenDimensions.w < 1920 && saveMenuPanelScreenDimensions.h < 1080 )
	{
		if (!saveButtonTexture.loadFromFile("Buttons/save1280x720.png", saveMenuRenderer))
		{
			cout << "Failed to load tile set texture!\n";
			success = false;
		}	
	}
	//Load 1920x1080 resolution button texture
	else if (saveMenuPanelScreenDimensions.w >= 1920 && saveMenuPanelScreenDimensions.h >= 1080)
	{
		if (!saveButtonTexture.loadFromFile("Buttons/save.png", saveMenuRenderer))
		{
			cout << "Failed to load tile set texture!\n";
			success = false;
		}
	}
	
		//Set save button position
		saveButton = { saveMenuPanelScreenDimensions.w / 2 - saveMenuPanelButtonDimensions.w / 2,saveMenuPanelScreenDimensions.h / 4 * 3 - saveMenuPanelButtonDimensions.h / 2, saveMenuPanelButtonDimensions.w, saveMenuPanelButtonDimensions.h };

		//Load clips of the button
		saveButtonClips[buttonNormal].x = 0;
		saveButtonClips[buttonNormal].y = 0;
		saveButtonClips[buttonNormal].h = saveMenuPanelButtonDimensions.h;
		saveButtonClips[buttonNormal].w = saveMenuPanelButtonDimensions.w;
	
		saveButtonClips[buttonHighlighted].x = 0;
		saveButtonClips[buttonHighlighted].y = saveMenuPanelButtonDimensions.h;
		saveButtonClips[buttonHighlighted].h = saveMenuPanelButtonDimensions.h;
		saveButtonClips[buttonHighlighted].w = saveMenuPanelButtonDimensions.w;
	
		saveButtonClips[buttonPressed].x = 0;
		saveButtonClips[buttonPressed].y = saveMenuPanelButtonDimensions.h * 2;
		saveButtonClips[buttonPressed].h = saveMenuPanelButtonDimensions.h;
		saveButtonClips[buttonPressed].w = saveMenuPanelButtonDimensions.w;


	
	//Load  1280x720 resolution current font 
	if (saveMenuPanelScreenDimensions.w < 1920 && saveMenuPanelScreenDimensions.h < 1080)
	{
		saveMenuFont = TTF_OpenFont("TTF'S/Rasterized-Regular.ttf", 31);
		if (saveMenuFont == NULL)
		{
			cout << ("Failed to load lazy font! SDL_ttf Error ID : %s\n", TTF_GetError());
			success = false;
		}
		saveMenuFontH2 = TTF_OpenFont("TTF'S/Rasterized-Regular.ttf", 24);
		if (saveMenuFontH2 == NULL)
		{
			cout << ("Failed to load lazy font! SDL_ttf Error ID : %s\n", TTF_GetError());
			success = false;
		}
	}

	//Load  1920x1080 resolution current font
	else if (saveMenuPanelScreenDimensions.w >= 1920 && saveMenuPanelScreenDimensions.h >= 1080)
	{
		saveMenuFont = TTF_OpenFont("TTF'S/Rasterized-Regular.ttf", 70);
		if (saveMenuFont == NULL)
		{
			cout << ("Failed to load lazy font! SDL_ttf Error ID : %s\n", TTF_GetError());
			success = false;
		}
		saveMenuFontH2 = TTF_OpenFont("TTF'S/Rasterized-Regular.ttf", 55);
		if (saveMenuFontH2 == NULL)
		{
			cout << ("Failed to load lazy font! SDL_ttf Error ID : %s\n", TTF_GetError());
			success = false;
		}


	}
	
	
	if (characterState != dead) 
	{
		textColor = { 255,215,0 };
		//Load congratulations text
		if (!CongratulationsTextTexture.loadFromRenderedText("You win ! ", textColor, saveMenuFont, saveMenuRenderer))
		{
			cout << ("Failed to load text texture ! SDL Error ID : %s", SDL_GetError());
			success = false;
		}
	}
	else 
	{
		textColor = { 179,0,0 };
		//Load congratulations text
		if (!CongratulationsTextTexture.loadFromRenderedText("You lose! ", textColor, saveMenuFont, saveMenuRenderer))
		{
			cout << ("Failed to load text texture ! SDL Error ID : %s", SDL_GetError());
			success = false;
		}
	}

	//Current font color
	textColor = { 255,255,255 };
		//Load current player result anouncement texture
		if (!CharacterStepsTexture.loadFromRenderedText(characterStepsText, textColor, saveMenuFont, saveMenuRenderer))
		{
			cout << ("Failed to load text texture ! SDL Error ID : %s", SDL_GetError());
			success = false;
		}
		//Load current player result anouncement texture
		if (!TimerTexture.loadFromRenderedText(timerText, textColor, saveMenuFontH2, saveMenuRenderer))
		{
			cout << ("Failed to load text texture ! SDL Error ID : %s", SDL_GetError());
			success = false;
		}
		//Load current player result anouncement texture
		if (!CollectablesTexture.loadFromRenderedText(collectablesText, textColor, saveMenuFontH2, saveMenuRenderer))
		{
			cout << ("Failed to load text texture ! SDL Error ID : %s", SDL_GetError());
			success = false;
		}
		winSound = Mix_LoadWAV("Sounds/WinStage.wav");
		if (winSound == NULL)
		{
			cout << ("Failed to load music file! SDL_mixer Error ID: %s\n", Mix_GetError());
			success = false;
		}
	


	return success;
}











void SaveMenu(SDL_Renderer* gameRenderer, SDL_Window* gameWindow, ConstantParameters currentConstantParameters, int characterSteps , int timer , int collectablesScore, int currentCharacterState)
{
	SDL_StartTextInput();
	//Get renderer value 
	saveMenuRenderer = gameRenderer;
	//Get window value 
	saveMenuWindow = gameWindow;
	//Get character steps value
	characterCurrentSteps = characterSteps;
	//Define character state 
	characterState = currentCharacterState;
	//Get current panel resolution-dependent needed global parameters
	saveMenuPanelScreenDimensions = currentConstantParameters.getScreenDimensions();
	saveMenuPanelButtonDimensions = currentConstantParameters.getButtonDimensions();

	//Stores current game state
	string gameState = "";
	if (currentCharacterState != dead) 
	{
		gameState = "won";
	}
	else {
		gameState = "lost";
	}
	//Parses string for current player result announcent texture 
	characterStepsText = "Steps : " + to_string(characterCurrentSteps);
	
	
	//Parses string for current timer announcent texture 
	timerText = "Time : " + to_string(timer) + " s" ;
	

	//Parses string for current collectables score announcent texture 
	collectablesText = "Trophies : " + to_string(collectablesScore);



		//Load menu media
		if (!saveMenuMedia())
		{
			cout << ("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Play once the winning sound
			Mix_PlayChannel(-1, winSound, 0);
			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{

					//User requests quit
					if (e.type == SDL_QUIT)
					{

						quit = true;
					}

				}
				if (characterState == dead) 
				{
					//clears screen renderer
					SDL_SetRenderDrawColor(saveMenuRenderer, 0, 0, 0, 0xFF);
					
				}
				else if (characterState == alive || characterState == shielded || characterState == win) {
					//clears screen renderer
					SDL_SetRenderDrawColor(saveMenuRenderer, 250, 250, 210, 128);
				}
				SDL_RenderClear(saveMenuRenderer);
				//Render congratulations text
				CongratulationsTextTexture.render(saveMenuPanelScreenDimensions.w/2 - CongratulationsTextTexture.getWidth()/2 , saveMenuPanelScreenDimensions.h/8, saveMenuRenderer);
				//Render player result announcement texture
				CharacterStepsTexture.render(saveMenuPanelScreenDimensions.w / 2 - CharacterStepsTexture.getWidth()/2 , saveMenuPanelScreenDimensions.h / 4 , saveMenuRenderer);
				//Render player timer announcement texture
				TimerTexture.render(saveMenuPanelScreenDimensions.w / 6 - TimerTexture.getWidth() , saveMenuPanelScreenDimensions.h / 4, saveMenuRenderer);
				//Render player collectables count  announcement texture
				CollectablesTexture.render(saveMenuPanelScreenDimensions.w / 4*3, saveMenuPanelScreenDimensions.h / 4, saveMenuRenderer);

				//Store current pressed key
				const Uint8* currentSaveMenuKey = SDL_GetKeyboardState(NULL);
				//Store current time 
				int currentTicks = SDL_GetTicks();
				//Check if input is written text or pressed key
				if ( currentSaveMenuKey != NULL  && e.type == SDL_TEXTINPUT || e.type == SDL_KEYDOWN  && currentTicks>= previousTicks + 250 )
				{
					//Add the text if it's text
					if (currentSaveMenuKey!=NULL && e.type == SDL_TEXTINPUT && playerName.length()<= MAX_PLAYER_NAME_WIDTH)
					{
						playerName += e.text.text[0];
						previousTicks = currentTicks;
					}
					//Delete a character if the backspace is pressed
					else if (  e.type = SDL_KEYDOWN && playerName.length() > 0  && currentSaveMenuKey[SDL_SCANCODE_BACKSPACE])
					{
						playerName = playerName.substr(0, playerName.length() - 1);
						previousTicks = currentTicks;
					}
				}
				//Loaded texture of the currently written player name
				LoadedTexture playerNameTexture;
				//Load texture of the currently written player name
				playerNameTexture.loadFromRenderedText(playerName, textColor, saveMenuFont, saveMenuRenderer);

				//Store current player name length
				int playerNameSize = playerName.length();
				//Calculate the horizontal position of the text to be central
				int playerNameX = saveMenuPanelScreenDimensions.w / 2 - playerNameTexture.getWidth()/2;
				//Calculate the vertical; position of the text to be central
				int playerNameY = saveMenuPanelScreenDimensions.h / 2 - playerNameTexture.getHeight()/2;
			
				//Render texture of the currently written player name
				playerNameTexture.render(playerNameX, playerNameY, saveMenuRenderer);

				//Determines current mouse location 
				int mouseX;
				int mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);

				//Checks if the mouse is on the button
				if (mouseX >= saveButton.x &&mouseX <= saveButton.x + saveButton.w&&
					mouseY >= saveButton.y && mouseY <= saveButton.y + saveButton.h)
				{
					//Checks if it's clicked
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						saveButtonTexture.render(saveButton.x, saveButton.y, saveMenuRenderer, &saveButtonClips[buttonPressed]);
						saveScore(playerName, characterSteps, timer, collectablesScore, gameState);
						quit = true;
						
					}
					else
					{
						saveButtonTexture.render(saveButton.x, saveButton.y, saveMenuRenderer, &saveButtonClips[buttonHighlighted]);
					}
				}
				else
				{

					saveButtonTexture.render(saveButton.x, saveButton.y, saveMenuRenderer, &saveButtonClips[buttonNormal]);

				}




				//Update screen
				SDL_RenderPresent(saveMenuRenderer);
			}


		}

}

void saveScore(string playerName, int characterSteps, int timer, int collectablesScore, string gameState)
{
	//Parses the name and the result of the player in the format for saving
	string saveFileText = playerName + " || " + to_string(characterSteps) + " || "  + to_string(timer) + " || " + to_string(collectablesScore) + " || " + gameState ;
	
	ofstream saveFile;
	//Open save file with flag for appending data
	saveFile.open("Save/save.txt", ofstream::app);
	
	saveFile << saveFileText << endl;
	//Close the file and end the panel
	saveFile.close();

	
}