#include <SDL.h>
#undef main
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

//The window to be rendered to 
SDL_Window* menuWindow = NULL;

//The window renderer
SDL_Renderer* menuRenderer = NULL;


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();
//Loads tiles

void Game(SDL_Renderer* menuRenderer, SDL_Window* menuWindow, ConstantParameters currentConstantParameters);
void Scoreboard(SDL_Renderer* menuRenderer, SDL_Window* menuWindow, ConstantParameters currentConstantParameters);
void Instructions(SDL_Renderer* menuRenderer, SDL_Window* menuWindow, ConstantParameters currentConstantParameters);

//Defining menu buttons
LoadedTexture buttonStart;
LoadedTexture buttonScores;
LoadedTexture buttonInstructions;
LoadedTexture buttonExit;
//Defining menu buttons attributes
SDL_Rect startButtonBox;
SDL_Rect scoresButtonBox;
SDL_Rect instructionsButtonBox;
SDL_Rect exitButtonBox;
SDL_Rect menuTitleBox;

SDL_Rect buttonClips[3];
//Get current display properties
SDL_DisplayMode currentDisplay;
//Set parameters depending on the resolution
ConstantParameters currentConstantParameters;
//Resolution-dependent parameters needed for the currently shown panel
SDL_Rect menuScreenDimensions;
SDL_Rect menuButtonDimensions;

//Font to be used in the menu 
TTF_Font* menuFont;
SDL_Color menuFontColor = { 255, 255, 255, 255};
LoadedTexture titleTexture;

bool init()
{
	//Initialization flag
	bool success = true;



	//Initializes SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
	{
		cout << ("SDL couldn't initialize! SDL Error ID: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Sets texture filtering
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2"))
		{
			cout << ("Warning: Texture filtering not available  !");
		}
		

		//Gets properties of the current display
		SDL_GetCurrentDisplayMode(0, &currentDisplay);
		
		//Set current resolution-dependent parameters
		currentConstantParameters =  ConstantParameters(currentDisplay);
		//Set the separated from the structure resolution-dependent parameters
		menuScreenDimensions = currentConstantParameters.getScreenDimensions();
		menuButtonDimensions = currentConstantParameters.getButtonDimensions();
		
		//Creates window
		menuWindow = SDL_CreateWindow("Hidden", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, menuScreenDimensions.w, menuScreenDimensions.h, SDL_WINDOW_SHOWN);
		if (menuWindow == NULL)
		{
			cout << ("Window couldn't be created! SDL Error ID: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Creates renderer for window
			menuRenderer = SDL_CreateRenderer(menuWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (menuRenderer == NULL)
			{
				cout << ("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				
				//Sets default renderer's background color
				(menuRenderer, 0, 0, 0, 0xFF);

				//Initializes PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << ("SDL_image couldn't initialize! SDL_image Error ID: %s\n", IMG_GetError());
					success = false;
				}
				//Initializes SDL_ttf
				if (TTF_Init() == -1)
				{
					cout << ("SDL_ttf couldn't initialize! SDL_ttf Error ID: %s\n", TTF_GetError());
					success = false;
				}
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
				{
					cout << ("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
				

			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;
	//Load 1920x1080 resolution preset
	if (menuScreenDimensions.w >= 1920 && menuScreenDimensions.h >= 1080)
	{

		//Load start button texture  
		if (!buttonStart.loadFromFile("Buttons/start.png", menuRenderer))
		{
			cout << "Failed to load tile set texture!\n";
			success = false;
		}
		//Set start button position
		startButtonBox = { menuScreenDimensions.w / 2 - menuButtonDimensions.w / 2,(menuScreenDimensions.h - menuButtonDimensions.w ) / 2 , menuButtonDimensions.w, menuButtonDimensions.h };
		
		
		
		if (!buttonScores.loadFromFile("Buttons/scores.png", menuRenderer))
		{
			cout << "Failed to load tile set texture!\n";
			success = false;
		}
		//Set scoreboard button position
		scoresButtonBox = { menuScreenDimensions.w / 2 - menuButtonDimensions.w / 2,(menuScreenDimensions.h) / 2 , menuButtonDimensions.w, menuButtonDimensions.h };
		
		
		
		if (!buttonInstructions.loadFromFile("Buttons/info.png", menuRenderer))
		{
			cout << "Failed to load tile set texture!\n";
			success = false;
		}
		//Set instructions button position
		instructionsButtonBox = { menuScreenDimensions.w / 2 - menuButtonDimensions.w / 2,(menuScreenDimensions.h + menuButtonDimensions.w) / 2 , menuButtonDimensions.w, menuButtonDimensions.h };
		
		
		
		if (!buttonExit.loadFromFile("Buttons/exit.png", menuRenderer))
		{
			cout << "Failed to load tile set texture!\n";
			success = false;
		}
		//Set exit button position
		exitButtonBox = { menuScreenDimensions.w / 2 - menuButtonDimensions.w / 2,(menuScreenDimensions.h + menuButtonDimensions.w * 2) / 2 , menuButtonDimensions.w, menuButtonDimensions.h };

		
		//Set button clips for the textures
			buttonClips[buttonNormal].x = 0;
			buttonClips[buttonNormal].y = 0;
			buttonClips[buttonNormal].h = menuButtonDimensions.h;
			buttonClips[buttonNormal].w = menuButtonDimensions.w;

			buttonClips[buttonHighlighted].x = 0;
			buttonClips[buttonHighlighted].y = menuButtonDimensions.h;
			buttonClips[buttonHighlighted].h = menuButtonDimensions.h;
			buttonClips[buttonHighlighted].w = menuButtonDimensions.w;

			buttonClips[buttonPressed].x = 0;
			buttonClips[buttonPressed].y = menuButtonDimensions.h * 2;
			buttonClips[buttonPressed].h = menuButtonDimensions.h;
			buttonClips[buttonPressed].w = menuButtonDimensions.w;

			//Load current  menu font 
			menuFont = TTF_OpenFont("TTF'S/Rasterized-Regular.ttf", 150);
			if (menuFont == NULL)
			{
				cout << ("Failed to load menu font! SDL_ttf Error ID : %s\n", TTF_GetError());
				success = false;
			}
			titleTexture.loadFromRenderedText("HIDDEN", menuFontColor, menuFont, menuRenderer);
			menuTitleBox = { menuScreenDimensions.w / 2 - titleTexture.getWidth() / 2, (titleTexture.getHeight()/8) / 2,titleTexture.getWidth(), titleTexture.getHeight() };

	}

	//Load 1280x720 resolution preset
	else if (menuScreenDimensions.w < 1920 && menuScreenDimensions.h < 1080)
	{
		//Load tiles picture  
		if (!buttonStart.loadFromFile("Buttons/start1280x720.png", menuRenderer))
		{
			cout << "Failed to load tile set texture!\n";
			success = false;
		}
		//Set start button position
		startButtonBox = { menuScreenDimensions.w / 2 - menuButtonDimensions.w / 2,(menuScreenDimensions.h - menuButtonDimensions.w ) / 2 , menuButtonDimensions.w, menuButtonDimensions.h };
		if (!buttonScores.loadFromFile("Buttons/scores1280x720.png", menuRenderer))
		{
			cout << "Failed to load tile set texture!\n";
			success = false;
		}
		//Set scoreboard button position
		scoresButtonBox = { menuScreenDimensions.w / 2 - menuButtonDimensions.w / 2,(menuScreenDimensions.h ) / 2 , menuButtonDimensions.w, menuButtonDimensions.h };
		if (!buttonInstructions.loadFromFile("Buttons/info1280x720.png", menuRenderer))
		{
			cout << "Failed to load tile set texture!\n";
			success = false;
		}
		//Set instructions button position
		instructionsButtonBox = { menuScreenDimensions.w / 2 - menuButtonDimensions.w / 2,(menuScreenDimensions.h + menuButtonDimensions.w) / 2 , menuButtonDimensions.w, menuButtonDimensions.h };
		if (!buttonExit.loadFromFile("Buttons/exit1280x720.png", menuRenderer))
		{
			cout << "Failed to load tile set texture!\n";
			success = false;
		}
		//Set exit button position
		exitButtonBox = { menuScreenDimensions.w / 2 - menuButtonDimensions.w / 2,(menuScreenDimensions.h + menuButtonDimensions.w * 2) / 2 , menuButtonDimensions.w, menuButtonDimensions.h };

		//Set button clips for the textures
			buttonClips[buttonNormal].x = 0;
			buttonClips[buttonNormal].y = 0;
			buttonClips[buttonNormal].h = menuButtonDimensions.h;
			buttonClips[buttonNormal].w = menuButtonDimensions.w;

			buttonClips[buttonHighlighted].x = 0;
			buttonClips[buttonHighlighted].y = menuButtonDimensions.h;
			buttonClips[buttonHighlighted].h = menuButtonDimensions.h;
			buttonClips[buttonHighlighted].w = menuButtonDimensions.w;

			buttonClips[buttonPressed].x = 0;
			buttonClips[buttonPressed].y = menuButtonDimensions.h * 2;
			buttonClips[buttonPressed].h = menuButtonDimensions.h;
			buttonClips[buttonPressed].w = menuButtonDimensions.w;

			//Load current  menu font 
			menuFont = TTF_OpenFont("TTF'S/Rasterized-Regular.ttf", 66);
			if (menuFont == NULL)
			{
				cout << ("Failed to load menu font! SDL_ttf Error ID : %s\n", TTF_GetError());
				success = false;
			}
			titleTexture.loadFromRenderedText("HIDDEN", menuFontColor, menuFont, menuRenderer);

			menuTitleBox = { menuScreenDimensions.w / 2 - titleTexture.getWidth() / 2, (titleTexture.getHeight() / 8) / 2,titleTexture.getWidth(), titleTexture.getHeight() };

	}

	

	return success;
}

void close()
{
	//Free loaded images
	buttonStart.ClearTexture();
	buttonScores.ClearTexture();
	buttonInstructions.ClearTexture();
	buttonExit.ClearTexture();

	//Destroy window	
	SDL_DestroyRenderer(menuRenderer);
	SDL_DestroyWindow(menuWindow);
	menuWindow = NULL;
	menuRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}









int main()
{
	
	//Start up SDL and create window
	if (!init())
	{
		cout << ("Failed to initialize!\n");
	}
	else
	{
		//Load menu media
		if (!loadMedia())
		{
			cout << ("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;



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
				
				//clears screen renderer
				SDL_SetRenderDrawColor(menuRenderer, 36, 36, 36, 0xFF);
				SDL_RenderClear(menuRenderer);
				
				
				titleTexture.render(menuTitleBox.x, menuTitleBox.y, menuRenderer);
				
				
				
				
				//Determines current mouse location 
				int mouseX;
				int mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);

				//Checks if the mouse is on the start button
				if (mouseX >= startButtonBox.x &&mouseX <= startButtonBox.x + startButtonBox.w&&
					mouseY >= startButtonBox.y && mouseY <= startButtonBox.y + startButtonBox.h)
				{
					//Checks if it's clicked
					if (e.type == SDL_MOUSEBUTTONDOWN) 
					{
						buttonStart.render(startButtonBox.x, startButtonBox.y, menuRenderer, &buttonClips[buttonPressed]);
						Game(menuRenderer,  menuWindow, currentConstantParameters);
					}
					else 
					{
						buttonStart.render(startButtonBox.x, startButtonBox.y, menuRenderer, &buttonClips[buttonHighlighted]);
					}
				}
				else 
				{
					
						buttonStart.render(startButtonBox.x, startButtonBox.y, menuRenderer, &buttonClips[buttonNormal]);
					
				}
				
				//Checks if the mouse is on the scores button
				if (mouseX >= scoresButtonBox.x &&mouseX <= scoresButtonBox.x + scoresButtonBox.w&&
					mouseY >= scoresButtonBox.y && mouseY <= scoresButtonBox.y + scoresButtonBox.h)
				{
					//Checks if it's clicked
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						buttonScores.render(scoresButtonBox.x, scoresButtonBox.y, menuRenderer, &buttonClips[buttonPressed]);
						Scoreboard(menuRenderer, menuWindow, currentConstantParameters);
					}
					else
					{
						buttonScores.render(scoresButtonBox.x, scoresButtonBox.y, menuRenderer, &buttonClips[buttonHighlighted]);
					}
				}
				else
				{

					buttonScores.render(scoresButtonBox.x, scoresButtonBox.y, menuRenderer, &buttonClips[buttonNormal]);

				}
				//Checks if the mouse is on the info button
				if (mouseX >= instructionsButtonBox.x &&mouseX <= instructionsButtonBox.x + instructionsButtonBox.w&&
					mouseY >= instructionsButtonBox.y && mouseY <= instructionsButtonBox.y + instructionsButtonBox.h)
				{
					//Checks if it's clicked
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						buttonInstructions.render(instructionsButtonBox.x, instructionsButtonBox.y, menuRenderer, &buttonClips[buttonPressed]);
						Instructions(menuRenderer, menuWindow, currentConstantParameters);
					}
					else
					{
						buttonInstructions.render(instructionsButtonBox.x, instructionsButtonBox.y, menuRenderer, &buttonClips[buttonHighlighted]);
					}
				}
				else
				{

					buttonInstructions.render(instructionsButtonBox.x, instructionsButtonBox.y, menuRenderer, &buttonClips[buttonNormal]);

				}
				//Checks if the mouse is on the exit button
				if (mouseX >= exitButtonBox.x &&mouseX <= exitButtonBox.x + exitButtonBox.w&&
					mouseY >= exitButtonBox.y && mouseY <= exitButtonBox.y + exitButtonBox.h)
				{
					//Checks if it's clicked
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						buttonExit.render(exitButtonBox.x, exitButtonBox.y, menuRenderer, &buttonClips[buttonPressed]);
						
						quit = true;
					}
					else
					{
						buttonExit.render(exitButtonBox.x, exitButtonBox.y, menuRenderer, &buttonClips[buttonHighlighted]);
					}
				}
				else
				{

					buttonExit.render(exitButtonBox.x, exitButtonBox.y, menuRenderer, &buttonClips[buttonNormal]);

				}
				

				//Update screen
				SDL_RenderPresent(menuRenderer);
			}


		}
	}

	//Free resources and close SDL
	close();

	return 0;
}