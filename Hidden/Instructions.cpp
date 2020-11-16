#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
using namespace std;

//Custom libraries

#include "Constants.h"
#include "Character.h"
#include "LoadedTexture.h"
#include "MappingTilling.h"
#include "ConstantParameters.h"

//The window to be rendered to 
SDL_Window* instructionsWindow = NULL;

//The window renderer
SDL_Renderer* instructionsRenderer = NULL;



//Loaded back button texture
LoadedTexture buttonBack;


//Loaded first 3 lines of the instructions text texutures
LoadedTexture InstructionsTexture[3];
//Loaded buttons instructions textures
LoadedTexture InstructionsButtons[5];

//Loaded footer of the instructions text textures
LoadedTexture InstructionsTextureFooter;


//Stored dimensions of the back button
SDL_Rect backButtonBox;
//Button clips to be used for rendering
SDL_Rect buttonInstructionsClips[3];
//Stored first font of the panel
TTF_Font* instructionsFontH1;
//Stored second font of the panel
TTF_Font* instructionsFontH2;
//Stored third font of the panel
TTF_Font* instructionsFontH3;
//Stored fourth font of the panel
TTF_Font* instructionsFontH4;

//Stores resolution-dependent parameters for current panel
SDL_Rect instructionsPanelScreenDimensions;
SDL_Rect instructionsPanelButtonDimensions;

bool instructionsMedia()
{
	//Loading success flag
	bool success = true;
	//Load first font of the panel
	if (instructionsPanelScreenDimensions.w < 1920 && instructionsPanelScreenDimensions.h < 1080)
	{
		instructionsFontH1 = TTF_OpenFont("TTF'S/Rasterized-Regular.ttf", 32);
		if (instructionsFontH1 == NULL)
		{
			cout << ("Failed to load lazy font! SDL_ttf Error ID : %s\n", TTF_GetError());
			success = false;
		}
		//Load second font of the panel
		instructionsFontH2 = TTF_OpenFont("TTF'S/Rasterized-Regular.ttf", 16);
		if (instructionsFontH2 == NULL)
		{
			cout << ("Failed to load lazy font! SDL_ttf Error ID : %s\n", TTF_GetError());
			success = false;
		}
		//Load third font of the panel
		instructionsFontH3 = TTF_OpenFont("TTF'S/Rasterized-Regular.ttf", 13);
		if (instructionsFontH3 == NULL)
		{
			cout << ("Failed to load lazy font! SDL_ttf Error ID : %s\n", TTF_GetError());
			success = false;
		}
		//Load fourth font of the panel
		instructionsFontH4 = TTF_OpenFont("TTF'S/Rasterized-Regular.ttf", 9);
		if (instructionsFontH4 == NULL)
		{
			cout << ("Failed to load lazy font! SDL_ttf Error ID : %s\n", TTF_GetError());
			success = false;
		}
	}
	else if (instructionsPanelScreenDimensions.w >= 1920 && instructionsPanelScreenDimensions.h >= 1080)
	{
		instructionsFontH1 = TTF_OpenFont("TTF'S/Rasterized-Regular.ttf", 70);
		if (instructionsFontH1 == NULL)
		{
			cout << ("Failed to load lazy font! SDL_ttf Error ID : %s\n", TTF_GetError());
			success = false;
		}
		//Load second font of the panel
		instructionsFontH2 = TTF_OpenFont("TTF'S/Rasterized-Regular.ttf", 35);
		if (instructionsFontH2 == NULL)
		{
			cout << ("Failed to load lazy font! SDL_ttf Error ID : %s\n", TTF_GetError());
			success = false;
		}
		//Load third font of the panel
		instructionsFontH3 = TTF_OpenFont("TTF'S/Rasterized-Regular.ttf", 30);
		if (instructionsFontH3 == NULL)
		{
			cout << ("Failed to load lazy font! SDL_ttf Error ID : %s\n", TTF_GetError());
			success = false;
		}
		//Load fourth font of the panel
		instructionsFontH4 = TTF_OpenFont("TTF'S/Rasterized-Regular.ttf", 22);
		if (instructionsFontH4 == NULL)
		{
			cout << ("Failed to load lazy font! SDL_ttf Error ID : %s\n", TTF_GetError());
			success = false;
		}
	}
	
	
		//Current font color
		SDL_Color textColor = { 255,255, 255 };
		//Render first line of the first 3 of the instructions
		if (!InstructionsTexture[0].loadFromRenderedText("Hidden", textColor, instructionsFontH1, instructionsRenderer))
		{
			cout << ("Failed to render text texture!\n");
			success = false;
		}
		//Render second line of the first 3 of the instructions
		if (!InstructionsTexture[1].loadFromRenderedText("Find the hidden treasures, don't get caught by the crawler or in a trap ", textColor, instructionsFontH2, instructionsRenderer))
		{
			cout << ("Failed to render text texture!\n");
			success = false;
		}
		//Render third line of the first 3 of the instructions
		if (!InstructionsTexture[2].loadFromRenderedText("Controls", textColor, instructionsFontH3, instructionsRenderer))
		{
			cout << ("Failed to render text texture!\n");
			success = false;
		}


		//Render first buttton of the fourth described 
		if (!InstructionsButtons[0].loadFromRenderedText("w - up", textColor, instructionsFontH4, instructionsRenderer))
		{
			cout << ("Failed to render text texture!\n");
			success = false;
		}
		//Render second buttton of the fourth described 
		if (!InstructionsButtons[1].loadFromRenderedText("s - down", textColor, instructionsFontH4, instructionsRenderer))
		{
			cout << ("Failed to render text texture!\n");
			success = false;
		}
		//Render third buttton of the fourth described 
		if (!InstructionsButtons[2].loadFromRenderedText("a - left", textColor, instructionsFontH4, instructionsRenderer))
		{
			cout << ("Failed to render text texture!\n");
			success = false;
		}
		//Render fourth buttton of the fourth described 
		if (!InstructionsButtons[3].loadFromRenderedText("d - right", textColor, instructionsFontH4, instructionsRenderer))
		{
			cout << ("Failed to render text texture!\n");
			success = false;
		}
		if (!InstructionsButtons[4].loadFromRenderedText("m - mute", textColor, instructionsFontH4, instructionsRenderer))
		{
			cout << ("Failed to render text texture!\n");
			success = false;
		}



		//Render instructions panel footer text texture
		if (!InstructionsTextureFooter.loadFromRenderedText("Some trophies are for points, some are traps", textColor, instructionsFontH4, instructionsRenderer))
		{
			cout << ("Failed to render text texture!\n");
			success = false;
		}
		//Load 1280x720 resolution button preset
	if (instructionsPanelScreenDimensions.w < 1920 && instructionsPanelScreenDimensions.h < 1080)
	{
		if (!buttonBack.loadFromFile("Buttons/back1280x720.png", instructionsRenderer))
		{
			cout << "Failed to load tile set texture!\n";
			success = false;
		}
	}
		//Load 1920x1080 resolution button preset
	else if (instructionsPanelScreenDimensions.w >= 1920 && instructionsPanelScreenDimensions.h >= 1080)
	{

		if (!buttonBack.loadFromFile("Buttons/back.png", instructionsRenderer))
		{
			cout << "Failed to load tile set texture!\n";
			success = false;
		}
	}
	//Render back button texture
	
	
	
	



		//Set button clips 
		buttonInstructionsClips[buttonNormal].x = 0;
		buttonInstructionsClips[buttonNormal].y = 0;
		buttonInstructionsClips[buttonNormal].h = instructionsPanelButtonDimensions.h;
		buttonInstructionsClips[buttonNormal].w = instructionsPanelButtonDimensions.w;

		buttonInstructionsClips[buttonHighlighted].x = 0;
		buttonInstructionsClips[buttonHighlighted].y = instructionsPanelButtonDimensions.h;
		buttonInstructionsClips[buttonHighlighted].h = instructionsPanelButtonDimensions.h;
		buttonInstructionsClips[buttonHighlighted].w = instructionsPanelButtonDimensions.w;

		buttonInstructionsClips[buttonPressed].x = 0;
		buttonInstructionsClips[buttonPressed].y = instructionsPanelButtonDimensions.h * 2;
		buttonInstructionsClips[buttonPressed].h = instructionsPanelButtonDimensions.h;
		buttonInstructionsClips[buttonPressed].w = instructionsPanelButtonDimensions.w;


	


	return success;
}










void Instructions(SDL_Renderer* menuRenderer, SDL_Window* menuWindow, ConstantParameters currentConstantParameters)
{
	//Set current panel renderer
	instructionsRenderer = menuRenderer;
	//Set current panel window
	instructionsWindow = menuWindow;
	//Get resolution-dependent parameters for current panel
	instructionsPanelScreenDimensions = currentConstantParameters.getScreenDimensions();
	instructionsPanelButtonDimensions = currentConstantParameters.getButtonDimensions();
	
		//Load currently needed media
		if (!instructionsMedia())
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
				SDL_SetRenderDrawColor(instructionsRenderer, 72, 72, 72, 0xFF);
				SDL_RenderClear(instructionsRenderer);
				//Determines current mouse location 
				
				for (int currentText = 0; currentText < 3; currentText++) 
				{
					//Render first 3 lines of instructions + 10 px downwards for every line of instructions (relatively to 1920x1080 resolution)
					InstructionsTexture[currentText].render(instructionsPanelScreenDimensions.w / 2 - InstructionsTexture[currentText].getWidth() / 2,
						int(instructionsPanelScreenDimensions.h /5.4 + InstructionsTexture[0].getHeight() * currentText + (instructionsPanelScreenDimensions.h /108)*currentText),
						instructionsRenderer);
				}
				for (int currentText = 0; currentText < 5; currentText++)
				{
					//Render under the first 3 lines of instructions in 2 columns  with 50 px downwards + 10 px downwards for every line of instructions (relatively to 1920x1080 resolution)
					InstructionsButtons[currentText].render(instructionsPanelScreenDimensions.w / 2 - InstructionsButtons[currentText].getWidth()/2 ,
						int(instructionsPanelScreenDimensions.h / 5.4 + (InstructionsTexture[0].getHeight() * 3 + (instructionsPanelScreenDimensions.h / 108) * 3 +
						(instructionsPanelScreenDimensions.h / 21.6))  + InstructionsButtons[currentText].getHeight() * currentText )
						, instructionsRenderer);
				}
				//Render under the second 5 lines of instructions with 50 px downwards + 10 px downwards for every line of instructions (relatively to 1920x1080 resolution)
				InstructionsTextureFooter.render(instructionsPanelScreenDimensions.w / 2 - InstructionsTextureFooter.getWidth()/2,
					int(instructionsPanelScreenDimensions.h / 5.4 + InstructionsTexture[0].getHeight() * 3 + InstructionsButtons[1].getHeight() * 5 + (instructionsPanelScreenDimensions.h / 108) * 8 + 
					(instructionsPanelScreenDimensions.h / 21.6)), instructionsRenderer);


				//Store button dimensions
				//Render under the second footer line of instructions with 50 px downwards + 10 px downwards for every line of instructions (relatively to 1920x1080 resolution)
				backButtonBox.x = instructionsPanelScreenDimensions.w / 2 - instructionsPanelButtonDimensions.w / 2;
				backButtonBox.y = int(instructionsPanelScreenDimensions.h / 5.4 + InstructionsTexture[0].getHeight() * 3 + InstructionsButtons[1].getHeight() * 4 +
					(instructionsPanelScreenDimensions.h / 108) * 7 + InstructionsTextureFooter.getHeight() + (instructionsPanelScreenDimensions.h / 21.6) * 2);

				backButtonBox.h = instructionsPanelButtonDimensions.h;
				backButtonBox.w = instructionsPanelButtonDimensions.w;

				//Get current mouse position
				int mouseX;
				int mouseY;

				SDL_GetMouseState(&mouseX, &mouseY);
				
				//Checks if the mouse is on the button
				if (mouseX >= backButtonBox.x &&mouseX <= backButtonBox.x + backButtonBox.w&&
					mouseY >= backButtonBox.y && mouseY <= backButtonBox.y + backButtonBox.h)
				{
					//Checks if it's clicked
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						buttonBack.render(backButtonBox.x, backButtonBox.y, instructionsRenderer, &buttonInstructionsClips[buttonPressed]);
						
						quit = true;
					}
					else
					{
						buttonBack.render(backButtonBox.x, backButtonBox.y, instructionsRenderer, &buttonInstructionsClips[buttonHighlighted]);
					}
				}
				else
				{

					buttonBack.render(backButtonBox.x, backButtonBox.y, instructionsRenderer, &buttonInstructionsClips[buttonNormal]);

				}

				//Update screen
				SDL_RenderPresent(instructionsRenderer);
			}
			
		}
		}
	

	