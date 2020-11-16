#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <array>
using namespace std;


//Custom libraries

#include "Constants.h"
#include "Character.h"
#include "LoadedTexture.h"
#include "MappingTilling.h"
#include "ConstantParameters.h"

//The window to be rendered to 
SDL_Window* scoreboardWindow = NULL;

//The window renderer
SDL_Renderer* scoreboardRenderer = NULL;

TTF_Font* scoreboardFont;
SDL_Color scoreboardTextColor = { 0,0,0 };


//Load currently needed media 
bool scoreboardMedia();


//Loaded back button texture
LoadedTexture backButtonTexture;
//Loaded scoreboard info text texture
LoadedTexture scoreboardTextTexture;
//Loaded  result of the current player 
LoadedTexture currentScoreResultTexture;
//Loaded name of the current player
LoadedTexture currentScoreNameTexture;
//Loaded  timer of the current player 
LoadedTexture currentTimerTexture;
//Loaded collectables score of the current player
LoadedTexture currentCollectablesScoreTexture;
//Loaded game state of the current player
LoadedTexture currentGameStateScoreTexture;
//Loaded scoreboard background texture
LoadedTexture scoreboardBackgroundTexture;
//Stored dimensions of the back button texture
SDL_Rect backButtonTextureBox ;
//Stored button clips for rendering
SDL_Rect backButtonClips[3];

//Stored top 5 found results
int scoreTop5Results[5];
//Stored names of the players whose are the top 5 results
string scoreTop5Names[5];
//Stored times of the players whose are the top 5 results
int scoreTop5Times[5];
//Stored collectables of the players whose are the top 5 results
int scoreTop5Collectables[5];
//Stored collectables of the players whose are the top 5 results
int scoreTop5States[5];

//Returns current scores in the DB/save file
void getScore();
//Stores resolution-dependent parameters needed for the currently shown panel
SDL_Rect scoreboardPanelScreenDimensions;
SDL_Rect scoreboardPanelButtonDimensions;
SDL_Rect scoreboardPanelScoreboardBackgroundDimensions;

bool scoreboardMedia()
{
	//Loading success flag
	bool success = true;

	//Load 1280x720 resolution textures preset
	if (scoreboardPanelScreenDimensions.w < 1920 && scoreboardPanelScreenDimensions.h < 1080)
	{
		if (!backButtonTexture.loadFromFile("Buttons/back1280x720.png", scoreboardRenderer))
		{
			cout << "Failed to load save button texture!\n";
			success = false;
		}
		if (!scoreboardBackgroundTexture.loadFromFile("Backgrounds/scoreboardBackground1280x720.png", scoreboardRenderer))
		{
			cout << "Failed to load scoreboard background texture!\n";
			success = false;
		}
	}
	//Load 1920x1080 resolution textures preset
	else if (scoreboardPanelScreenDimensions.w >= 1920 && scoreboardPanelScreenDimensions.h >= 1080)
	{
		if (!backButtonTexture.loadFromFile("Buttons/back.png", scoreboardRenderer))
		{
			cout << "Failed to load save button texture!\n";
			success = false;
		}
		if (!scoreboardBackgroundTexture.loadFromFile("Backgrounds/scoreboardBackground.png", scoreboardRenderer))
		{
			cout << "Failed to load scoreboard background texture!\n";
			success = false;
		}
	}
	  
	//Load scoreboard background texture
	


	//Set current panel back button position
		backButtonTextureBox =
		{int( scoreboardPanelScreenDimensions.w / 2 - scoreboardPanelButtonDimensions.w / 2),
			int(scoreboardPanelScreenDimensions.h / 5.4 + scoreboardPanelScoreboardBackgroundDimensions.h * 5 + scoreboardPanelScreenDimensions.h / 54 * 6),
			scoreboardPanelButtonDimensions.w, scoreboardPanelButtonDimensions.h };

		//Set button clips 
		backButtonClips[buttonNormal].x = 0;
		backButtonClips[buttonNormal].y = 0;
		backButtonClips[buttonNormal].h = scoreboardPanelButtonDimensions.h;
		backButtonClips[buttonNormal].w = scoreboardPanelButtonDimensions.w;

		backButtonClips[buttonHighlighted].x = 0;
		backButtonClips[buttonHighlighted].y = scoreboardPanelButtonDimensions.h;
		backButtonClips[buttonHighlighted].h = scoreboardPanelButtonDimensions.h;
		backButtonClips[buttonHighlighted].w = scoreboardPanelButtonDimensions.w;

		backButtonClips[buttonPressed].x = 0;
		backButtonClips[buttonPressed].y = scoreboardPanelButtonDimensions.h * 2;
		backButtonClips[buttonPressed].h = scoreboardPanelButtonDimensions.h;
		backButtonClips[buttonPressed].w = scoreboardPanelButtonDimensions.w;


	

		//Set 1280x720 resolution font preset
	if (scoreboardPanelScreenDimensions.w < 1920 && scoreboardPanelScreenDimensions.h < 1080)
	{
		scoreboardFont = TTF_OpenFont("TTF'S/Rasterized-Regular.ttf", 22);
		if (scoreboardFont == NULL)
		{
			cout << ("Failed to load lazy font! SDL_ttf Error ID : %s\n", TTF_GetError());
			success = false;
		}
	}
	//Set 1920x1080 resolution font preset
	else if (scoreboardPanelScreenDimensions.w >= 1920 && scoreboardPanelScreenDimensions.h >= 1080)
	{
		scoreboardFont = TTF_OpenFont("TTF'S/Rasterized-Regular.ttf", 50);
		if (scoreboardFont == NULL)
		{
			cout << ("Failed to load lazy font! SDL_ttf Error ID : %s\n", TTF_GetError());
			success = false;
		}
	}
	
		//Set Current font color
		SDL_Color textColor = { 255,255, 255 };
		//Renders scoreboard info text 
		if (!scoreboardTextTexture.loadFromRenderedText("TOP 5 : NAMES/TIMES/RESULTS/COLLECTABLES ", textColor, scoreboardFont, scoreboardRenderer))
		{
			cout << ("Failed to render text texture!\n");
			success = false;
		}


	
		return success;
	
}











void Scoreboard(SDL_Renderer* menuRenderer, SDL_Window* menuWindow, ConstantParameters currentConstantParameters)
{
	//Set the current top 5 result selection
	getScore();
	//Set current panel renderer
	scoreboardRenderer = menuRenderer;
	//Set current panel window
	scoreboardWindow = menuWindow;

	//Get resolution-dependent parameters needed for the current panel
	scoreboardPanelScreenDimensions = currentConstantParameters.getScreenDimensions();
	scoreboardPanelButtonDimensions = currentConstantParameters.getButtonDimensions();
	scoreboardPanelScoreboardBackgroundDimensions = currentConstantParameters.getScoreboardBackgroundDimensions();

	//Load current panel media
	if (!scoreboardMedia())
	{
		cout << ("Failed to load media!\n");
	}
	else
	{
		//Loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;



		//While application is running
		while (!quit)
		{
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{

				//If user requests quit
				if (e.type == SDL_QUIT)
				{

					quit = true;
				}

			}
			//Render clear screen 
			SDL_SetRenderDrawColor(scoreboardRenderer, 72, 72, 72, 0xFF);
			SDL_RenderClear(scoreboardRenderer);

			//Render current 5 players's names and results
			for (int top5Results = 0; top5Results < 5; top5Results++)
			{
				currentScoreNameTexture.loadFromRenderedText(scoreTop5Names[top5Results], scoreboardTextColor, scoreboardFont, scoreboardRenderer);
				currentScoreResultTexture.loadFromRenderedText(to_string(scoreTop5Results[top5Results]), scoreboardTextColor, scoreboardFont, scoreboardRenderer);
				currentTimerTexture.loadFromRenderedText((to_string(scoreTop5Times[top5Results])+ " s " ), scoreboardTextColor, scoreboardFont, scoreboardRenderer);
				currentCollectablesScoreTexture.loadFromRenderedText(("T " + to_string(scoreTop5Collectables[top5Results])), scoreboardTextColor, scoreboardFont, scoreboardRenderer);
				
				if (scoreTop5States[top5Results] == alive) {
					currentGameStateScoreTexture.loadFromRenderedText("  Won", scoreboardTextColor, scoreboardFont, scoreboardRenderer);
				}
				else if (scoreTop5States[top5Results] == dead) {
					currentGameStateScoreTexture.loadFromRenderedText("  Lost", scoreboardTextColor, scoreboardFont, scoreboardRenderer);
				}





				//Render 200 px (relatively to 1920x1080px resolution) under the top of the screen, middle of the width, bottom and top borders overlayered
				scoreboardBackgroundTexture.render(scoreboardPanelScreenDimensions.w / 2 - scoreboardPanelScoreboardBackgroundDimensions.w / 2,  int(scoreboardPanelScreenDimensions.h /5.4 + scoreboardPanelScoreboardBackgroundDimensions.h *top5Results + scoreboardPanelScreenDimensions.h /54 * top5Results), scoreboardRenderer);
				//Render at the first box of the background with left and top border passed (at the 30th px of the texture width, relatively to the 1920x1080 resolution texture size) 
				currentScoreNameTexture.render(scoreboardPanelScreenDimensions.w / 2 - scoreboardPanelScoreboardBackgroundDimensions.w / 2 + scoreboardPanelScreenDimensions.w /64,
					int(scoreboardPanelScreenDimensions.h / 5.4 + scoreboardPanelScoreboardBackgroundDimensions.h *top5Results + scoreboardPanelScreenDimensions.h / 54 * top5Results + scoreboardPanelScreenDimensions.h /36), scoreboardRenderer);
				//Render at the second box of the background with left and top border passed
				currentTimerTexture.render(scoreboardPanelScreenDimensions.w / 2 - scoreboardPanelScoreboardBackgroundDimensions.w / 2 + scoreboardPanelScoreboardBackgroundDimensions.w / 3.94,
					int(scoreboardPanelScreenDimensions.h / 5.4 + scoreboardPanelScoreboardBackgroundDimensions.h *top5Results + scoreboardPanelScreenDimensions.h / 54 * top5Results + scoreboardPanelScreenDimensions.h / 36), scoreboardRenderer);
				//Render at the third box of the background with passed left border 
				currentScoreResultTexture.render(scoreboardPanelScreenDimensions.w / 2 - scoreboardPanelScoreboardBackgroundDimensions.w / 2 + scoreboardPanelScoreboardBackgroundDimensions.w /1.98,
					int(scoreboardPanelScreenDimensions.h / 5.4 + scoreboardPanelScoreboardBackgroundDimensions.h *top5Results + scoreboardPanelScreenDimensions.h / 54 * top5Results + scoreboardPanelScreenDimensions.h /36), scoreboardRenderer);
				//Render at the fourth box of the background with passed left border 
				currentCollectablesScoreTexture.render(scoreboardPanelScreenDimensions.w / 2 - scoreboardPanelScoreboardBackgroundDimensions.w / 2 + scoreboardPanelScoreboardBackgroundDimensions.w /1.36,
					int(scoreboardPanelScreenDimensions.h / 5.4 + scoreboardPanelScoreboardBackgroundDimensions.h *top5Results + scoreboardPanelScreenDimensions.h / 54 * top5Results + scoreboardPanelScreenDimensions.h /36), scoreboardRenderer);
				//Render at the fifth box of the background with passed left border 
				currentGameStateScoreTexture.render(scoreboardPanelScreenDimensions.w / 2 - scoreboardPanelScoreboardBackgroundDimensions.w / 2 + scoreboardPanelScoreboardBackgroundDimensions.w / 1.163,
					int(scoreboardPanelScreenDimensions.h / 5.4 + scoreboardPanelScoreboardBackgroundDimensions.h *top5Results + scoreboardPanelScreenDimensions.h / 54 * top5Results + scoreboardPanelScreenDimensions.h / 36), scoreboardRenderer);

			}

			//Render button
			//Checks if the mouse is on the button
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			if (mouseX >= backButtonTextureBox.x &&mouseX <= backButtonTextureBox.x + backButtonTextureBox.w&&
				mouseY >= backButtonTextureBox.y && mouseY <= backButtonTextureBox.y + backButtonTextureBox.h)
			{
				//Checks if it's clicked
				if (e.type == SDL_MOUSEBUTTONDOWN)
				{
					backButtonTexture.render(backButtonTextureBox.x, backButtonTextureBox.y, scoreboardRenderer, &backButtonClips[buttonPressed]);
					quit = true;

				}
				else
				{
					backButtonTexture.render(backButtonTextureBox.x, backButtonTextureBox.y, scoreboardRenderer, &backButtonClips[buttonHighlighted]);
				}
			}
			else
			{

				backButtonTexture.render(backButtonTextureBox.x, backButtonTextureBox.y, scoreboardRenderer, &backButtonClips[buttonNormal]);

			}

		
			//Render over the scoreboard, 100 of the top (relatively to 1920x1080 resolution)
			scoreboardTextTexture.render(scoreboardPanelScreenDimensions.w / 2 - scoreboardTextTexture.getWidth()/2, int(scoreboardPanelScreenDimensions.h/10.8) , scoreboardRenderer);



			//Update screen
			SDL_RenderPresent(scoreboardRenderer);

		}

	}
}


void getScore()
{
	//Stored previous line of the DB/save file
	string previousLine = "";
	//Read file 
	ifstream saveFile;
	saveFile.open("Save/save.txt");
	//Stored current line of the DB/save file 
	string currentLine = "something";

	//Stored 5 parameters for top 5 results and names
	int scoreTop1Result = 5000000; string scoreTop1Name = "No result"; int scoreTop1Time = 0; int scoreTop1Collectable = 0; int scoreTop1State = 500;
	int scoreTop2Result = 5000000; string scoreTop2Name = "No result"; int scoreTop2Time = 0; int scoreTop2Collectable = 0; int scoreTop2State = 500;
	int scoreTop3Result = 5000000; string scoreTop3Name = "No result"; int scoreTop3Time = 0; int scoreTop3Collectable = 0; int scoreTop3State = 500;
	int scoreTop4Result = 5000000; string scoreTop4Name = "No result"; int scoreTop4Time = 0; int scoreTop4Collectable = 0; int scoreTop4State = 500;
	int scoreTop5Result = 5000000; string scoreTop5Name = "No result"; int scoreTop5Time = 0; int scoreTop5Collectable = 0; int scoreTop5State = 500;

		//Check if the current line of DB and previous line of DB are equal => end of file
		while (currentLine != previousLine) 
		{
			//Return current line of DB/save file 
			getline(saveFile, currentLine);
			//Check again if the current line of DB and previous line of DB are equal => end of file
			if (currentLine == previousLine)
			{
				break;
			}
			else
			{
				//Gets player name from the string, before delimeter (||)
				string currentName = currentLine.substr(0, currentLine.find("||"));
				//Parses int from save file text, passed delimeter (||)
				string substr1 = currentLine.substr(currentLine.find("||") + 3, currentLine.length());
				int currentResult = stoi(substr1.substr(0, substr1.find("||")), nullptr, 10);
				string substr2 = substr1.substr(substr1.find("||") + 3, substr1.length());
				int currentTimer = stoi(substr2.substr(0, substr2.find("||")), nullptr, 10);
				string substr3 = substr2.substr(substr2.find("||") + 3, substr2.length());
				int currentCollectables = stoi(substr3.substr(0, substr3.find("||")), nullptr, 10);
				string substr4 = substr3.substr(substr3.find("||") + 3, substr3.length());
				int currentState = 0;
				if (substr4 == "won") 
				{
					currentState = alive;
				}
				else if (substr4 == "lost") 
				{ 
					currentState = dead;
				}
				

				
					//Check if the result is in TOP 1 
					if (currentState < scoreTop1State || (currentResult <= scoreTop1Result && currentState <= scoreTop1State))
					{
						scoreTop5Result = scoreTop4Result; scoreTop5Name = scoreTop4Name; scoreTop5Time = scoreTop4Time; scoreTop5Collectable = scoreTop4Collectable; scoreTop5State = scoreTop4State;
						scoreTop4Result = scoreTop3Result; scoreTop4Name = scoreTop3Name; scoreTop4Time = scoreTop3Time; scoreTop4Collectable = scoreTop3Collectable; scoreTop4State = scoreTop3State;
						scoreTop3Result = scoreTop2Result; scoreTop3Name = scoreTop2Name; scoreTop3Time = scoreTop2Time; scoreTop3Collectable = scoreTop2Collectable; scoreTop3State = scoreTop2State;
						scoreTop2Result = scoreTop1Result; scoreTop2Name = scoreTop1Name; scoreTop2Time = scoreTop1Time; scoreTop2Collectable = scoreTop1Collectable; scoreTop2State = scoreTop1State;
						scoreTop1Result = currentResult; scoreTop1Name = currentName; scoreTop1Time = currentTimer; scoreTop1Collectable = currentCollectables; scoreTop1State = currentState;
					}
					//Check if the result is in TOP 2 
					else if ( currentState < scoreTop2State  || (currentResult <= scoreTop2Result && currentState <= scoreTop2State))
					{
						scoreTop5Result = scoreTop4Result; scoreTop5Name = scoreTop4Name; scoreTop5Time = scoreTop4Time; scoreTop5Collectable = scoreTop4Collectable; scoreTop5State = scoreTop4State;
						scoreTop4Result = scoreTop3Result; scoreTop4Name = scoreTop3Name; scoreTop4Time = scoreTop3Time; scoreTop4Collectable = scoreTop3Collectable; scoreTop4State = scoreTop3State;
						scoreTop3Result = scoreTop2Result; scoreTop3Name = scoreTop2Name; scoreTop3Time = scoreTop2Time; scoreTop3Collectable = scoreTop2Collectable; scoreTop3State = scoreTop2State;
						scoreTop2Result = currentResult; scoreTop2Name = currentName; scoreTop2Time = currentTimer; scoreTop2Collectable = currentCollectables; scoreTop2State = currentState;
					}
					//Check if the result is in TOP 3
					else if (currentState < scoreTop3State || (currentResult <= scoreTop3Result && currentState <= scoreTop3State))
					{
						scoreTop5Result = scoreTop4Result; scoreTop5Name = scoreTop4Name; scoreTop5Time = scoreTop4Time; scoreTop5Collectable = scoreTop4Collectable; scoreTop5State = scoreTop4State;
						scoreTop4Result = scoreTop3Result; scoreTop4Name = scoreTop3Name; scoreTop4Time = scoreTop3Time; scoreTop4Collectable = scoreTop3Collectable; scoreTop4State = scoreTop3State;
						scoreTop3Result = currentResult; scoreTop3Name = currentName; scoreTop3Time = currentTimer; scoreTop3Collectable = currentCollectables; scoreTop3State = currentState;

					}
					//Check if the result is in TOP 4
					else if (currentState < scoreTop4State || (currentResult <= scoreTop4Result && currentState <= scoreTop4State))
					{
						scoreTop5Result = scoreTop4Result; scoreTop5Name = scoreTop4Name; scoreTop5Time = scoreTop4Time; scoreTop5Collectable = scoreTop4Collectable; scoreTop5State = scoreTop4State;
						scoreTop4Result = currentResult; scoreTop4Name = currentName; scoreTop4Time = currentTimer; scoreTop4Collectable = currentCollectables; scoreTop4State = currentState;
					}
					//Check if the result is in TOP 5
					else if (currentState < scoreTop5State || (currentResult <= scoreTop5Result && currentState <= scoreTop5State))
					{
						scoreTop5Result = currentResult; scoreTop5Name = currentName; scoreTop5Time = currentTimer; scoreTop5Collectable = currentCollectables;  scoreTop5State = currentState;
					}
			}
		}
		//Close file stream
		saveFile.close();
		//Store the results to be shown
		scoreTop5Results[0] = scoreTop1Result; 	scoreTop5Names[0] =  scoreTop1Name ; scoreTop5Times[0] =  scoreTop1Time ; scoreTop5Collectables[0] =  scoreTop1Collectable ;  scoreTop5States[0] =  scoreTop1State ; 
		scoreTop5Results[1] = scoreTop2Result; 	scoreTop5Names[1] =  scoreTop2Name ; scoreTop5Times[1] =  scoreTop2Time ; scoreTop5Collectables[1] =  scoreTop2Collectable ;  scoreTop5States[1] =  scoreTop2State ;
		scoreTop5Results[2] = scoreTop3Result; 	scoreTop5Names[2] =  scoreTop3Name ; scoreTop5Times[2] =  scoreTop3Time ; scoreTop5Collectables[2] =  scoreTop3Collectable ;  scoreTop5States[2] =  scoreTop3State ;
		scoreTop5Results[3] = scoreTop4Result; 	scoreTop5Names[3] =  scoreTop4Name ; scoreTop5Times[3] =  scoreTop4Time ; scoreTop5Collectables[3] =  scoreTop4Collectable ;  scoreTop5States[3] =  scoreTop4State ;
		scoreTop5Results[4] = scoreTop5Result; 	scoreTop5Names[4] =  scoreTop5Name ; scoreTop5Times[4] =  scoreTop5Time ; scoreTop5Collectables[4] =  scoreTop5Collectable ;  scoreTop5States[4] =  scoreTop5State ;

}