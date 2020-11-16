#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <SDL_mixer.h>
#include <math.h>
using namespace std; 



//Custom libraries

#include "Constants.h"
#include "Character.h"
#include "Enemy.h"
#include "LoadedTexture.h"
#include "MappingTilling.h"
#include "ConstantParameters.h"
#include "Collectable.h" 
//The window to be rendered to
SDL_Window* gameWindow = NULL;

//The window renderer
SDL_Renderer* gameRenderer = NULL;

//Scene textures
LoadedTexture gSplashTexture;
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();


//Loads tiles
bool setTiles();
//Checker for collision between 2 boxes
bool checkCollision(SDL_Rect a, SDL_Rect b);



//Stores game character
Character Player ;
//Stores enemies 
Enemy aiEnemy[MAX_ENEMIES] ;

//Array of level tiles 
Tile* tileSet[TOTAL_TILES];
//Texture for the tile sprites  
LoadedTexture gTileTexture;
//Character texture  
LoadedTexture gCharacterTexture;
//Enemy texture 
LoadedTexture gEnemyTexture;
//Array of tile types 
SDL_Rect gTileClips[TOTAL_TILE_SPRITES];
//Array of miner movement states
SDL_Rect minerClips[TOTAL_OBJECT_SPRITES];
//Loaded text font
TTF_Font* gFont ;
//Loaded teleport text texture
LoadedTexture gPreTeleportTextTexture;
//After teleport text top 
LoadedTexture gTextAfterTeleport1Texture;
//After teleport text bottom 
LoadedTexture gTextAfterTeleport2Texture;
//Current time of the program
int playerTicks = 0;
//Current time of the program
int enemyTicks = 0;
//Checks if teleport text should be shown
int teleportText = 0;
//Current rendered partition of the level
SDL_Rect currentLevelCamera;
//Loaded steps counter texture
LoadedTexture stepsTextTexture;
//Loaded collectables counter texture
LoadedTexture collectablesTextTexture;
//Loaded timer texture
LoadedTexture timerTextTexture;
//Loaded lifes counter texture
LoadedTexture lifesTextTexture;
//Sound alert texture
LoadedTexture gSoundTexture;
//Steps counter
int characterSteps = 0;
//Steps relative to the tiles 
int characterRealSteps = 0;
//Loaded music 
Mix_Music* loudTetris;
//Check if music is prompted to stop
int stopMusic = 0;

//Stores parameters depending on the resolution
ConstantParameters currentPanelConstantParameters;
//Stores resolution-dependent parameters needed for the currently shown panel
SDL_Rect gamePanelScreenDimensions;
SDL_Rect gamePanelTilesParameters;
SDL_Rect gamePanelCharacterParameters;
SDL_Rect gamePanelLevelParameters;
SDL_Rect characterTileParameters;
//Screen screen offset for rendering, depends on the resolution
int xOffset, yOffset = 0 ;
//Stores current level collectables count
int currentLevelCollectables = 0;
//Stores current level collectables types and properties
Collectable collectableSet[MAX_COLLECTABLE_COUNT];
//Clears game parameters
void clearParameters();

void SaveMenu(SDL_Renderer* gameRenderer, SDL_Window* gameWindow, ConstantParameters currentConstantParameters, int characterSteps , int timer, int collectablesScore, int characterState);


bool loadInGameMedia()
{
	//Loading success flag
	bool success = true;

	//Load 1280x720 resolution preset
	if (gamePanelScreenDimensions.w < 1920 && gamePanelScreenDimensions.h < 1080) {
		//Load tiles picture  
		if (!gTileTexture.loadFromFile("tiling/tiles1280x720.png", gameRenderer))
		{
			cout << "Failed to load tile set texture!\n";
			success = false;
		}
		if (!gCharacterTexture.loadFromFile("Characters/miner1280x720.png", gameRenderer))
		{
			cout << "Failed to load character  texture!\n";
			success = false;
		}
		if (!gEnemyTexture.loadFromFile("Characters/beetle1280x720.png", gameRenderer))
		{
			cout << "Failed to load character  texture!\n";
			success = false;
		}
		
		//Load music
		loudTetris = Mix_LoadMUS("Sounds/BackgroundMusic.mp3");
		if (loudTetris == NULL)
		{
			cout << ("Failed to load music file! SDL_mixer Error ID: %s\n", Mix_GetError());
			success = false;
		}
		//Load current font 
		gFont = TTF_OpenFont("TTF'S/Rasterized-Regular.ttf", 16);
		if (gFont == NULL)
		{
			cout << ("Failed to load lazy font! SDL_ttf Error ID : %s\n", TTF_GetError());
			success = false;
		}

	}

	//Load 1920x1080 resolution preset
	else if (gamePanelScreenDimensions.w >= 1920 && gamePanelScreenDimensions.h >= 1080) 
	{
		//Load tiles picture  
		if (!gTileTexture.loadFromFile("tiling/tiles.png", gameRenderer))
		{
			cout << "Failed to load tile set texture!\n";
			success = false;
		}
		if (!gCharacterTexture.loadFromFile("Characters/miner.png", gameRenderer))
		{
			cout << "Failed to load character texture!\n";
			success = false;
		}
		if (!gEnemyTexture.loadFromFile("Characters/beetle.png", gameRenderer))
		{
			cout << "Failed to load character texture!\n";
			success = false;
		}
		//Load music
		loudTetris = Mix_LoadMUS("Sounds/BackgroundMusic.mp3");
		if (loudTetris == NULL)
		{
			cout << ("Failed to load music file! SDL_mixer Error ID: %s\n", Mix_GetError());
			success = false;
		}
		//Load current font 
		gFont = TTF_OpenFont("TTF'S/Rasterized-Regular.ttf", 35);
		if (gFont == NULL)
		{
			cout << ("Failed to load lazy font! SDL_ttf Error ID : %s\n", TTF_GetError());
			success = false;
		}
	}
	
		
		
		//Current font color
		SDL_Color textColor = { 255,255, 255 };
		//Renders text
		if (!gPreTeleportTextTexture.loadFromRenderedText("Teleporting in 3 seconds ", textColor, gFont, gameRenderer))
		{
			cout<<("Failed to render teleport  texture!\n");
			success = false;
		}
		if (!gTextAfterTeleport1Texture.loadFromRenderedText("The character has been teleported to the top", textColor, gFont, gameRenderer))
		{
			cout << ("Failed to render after teleport text for top texture!\n");
			success = false;
		}
		if (!gTextAfterTeleport2Texture.loadFromRenderedText("The character has been teleported to the bottom", textColor, gFont, gameRenderer))
		{
			cout << ("Failed to render after teleport text for bottom texture!\n");
			success = false;
		}
		if (!gSoundTexture.loadFromRenderedText("Loud sound engaged ", textColor, gFont, gameRenderer))
		{
			cout << ("Failed to render sound text texture!\n");
			success = false;
		}
	
	//Set constants relatively to the current resolution

	//Load tile map
	if (!setTiles())
	{
		cout<<"Failed to load tile set!\n";
		success = false;
	}
	//Sets current level camera starting position
	currentLevelCamera = { 0, 0, gamePanelScreenDimensions.w, gamePanelScreenDimensions.h };

	//Set character starting positions
	Player = Character(gamePanelTilesParameters.w * 3 + gamePanelCharacterParameters.w / 2, gamePanelTilesParameters.h + gamePanelCharacterParameters.h / 2, gamePanelCharacterParameters.w, gamePanelCharacterParameters.h);
	
	//Set enemies positions
	aiEnemy[0] = Enemy(gamePanelTilesParameters.w * 4 + gamePanelCharacterParameters.w / 2, gamePanelTilesParameters.h + gamePanelCharacterParameters.h / 2, gamePanelCharacterParameters.w, gamePanelCharacterParameters.h);
	aiEnemy[1] = Enemy(gamePanelTilesParameters.w * 7 + gamePanelCharacterParameters.w / 2, gamePanelTilesParameters.h*26 + gamePanelCharacterParameters.h / 2, gamePanelCharacterParameters.w, gamePanelCharacterParameters.h);
	aiEnemy[2] = Enemy(gamePanelTilesParameters.w * 10 + gamePanelCharacterParameters.w / 2, gamePanelTilesParameters.h * 14 + gamePanelCharacterParameters.h / 2, gamePanelCharacterParameters.w, gamePanelCharacterParameters.h);
	aiEnemy[3] = Enemy(gamePanelTilesParameters.w * 3 + gamePanelCharacterParameters.w / 2, gamePanelTilesParameters.h * 7 + gamePanelCharacterParameters.h / 2, gamePanelCharacterParameters.w, gamePanelCharacterParameters.h);
	aiEnemy[4] = Enemy(gamePanelTilesParameters.w * 25 + gamePanelCharacterParameters.w / 2, gamePanelTilesParameters.h * 4 + gamePanelCharacterParameters.h / 2, gamePanelCharacterParameters.w, gamePanelCharacterParameters.h);
	aiEnemy[5] = Enemy(gamePanelTilesParameters.w * 5 + gamePanelCharacterParameters.w / 2, gamePanelTilesParameters.h * 9 + gamePanelCharacterParameters.h / 2, gamePanelCharacterParameters.w, gamePanelCharacterParameters.h);
	aiEnemy[6] = Enemy(gamePanelTilesParameters.w * 4 + gamePanelCharacterParameters.w / 2, gamePanelTilesParameters.h * 4 + gamePanelCharacterParameters.h / 2, gamePanelCharacterParameters.w, gamePanelCharacterParameters.h);
	aiEnemy[7] = Enemy(gamePanelTilesParameters.w * 26 + gamePanelCharacterParameters.w / 2, gamePanelTilesParameters.h * 3 + gamePanelCharacterParameters.h / 2, gamePanelCharacterParameters.w, gamePanelCharacterParameters.h);

	Player.setObjectClips(currentPanelConstantParameters);
	Player.setTexture(gCharacterTexture);

	for (int currentEnemy = 0; currentEnemy < MAX_ENEMIES; currentEnemy++)
	{
		aiEnemy[currentEnemy].setObjectClips(currentPanelConstantParameters);
		aiEnemy[currentEnemy].setTexture(gEnemyTexture);
	}
	

	//Define count of collectables for current level 

	currentLevelCollectables = 5;
	
	

	return success;
}


//Sets current camera position
SDL_Rect setCamera(SDL_Rect camera, SDL_Rect currentBox)
{
	//Center the camera over the object
	camera.x = 0;
	camera.y = (currentBox.y + gamePanelCharacterParameters.h / 2) - gamePanelScreenDimensions.h / 2;

	//Keep the camera in bounds

	//Checks if camera is vertiaclly out of bound 
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	//Checks if camera is vertiaclly out of bound 
	if (camera.y > gamePanelLevelParameters.h - camera.h)
	{
		camera.y = gamePanelLevelParameters.h - camera.h;
	}

	return camera;
}


bool setTiles()
{
	//Success flag
	bool tilesLoaded = true;
	int x = 0, y = 0;

	if (gamePanelLevelParameters.w == 1280 && gamePanelLevelParameters.h == 1440)
	{
		//The tile offsets
		xOffset = 4, yOffset = 4;
		x = xOffset, y = yOffset;

		//Map not fitting perfectly, needs 4px offset left and right horizontally, 4 px top and 5 px bottom vertically 
	}
	else if (gamePanelLevelParameters.w == 1920 && gamePanelLevelParameters.h == 2160)
	{
		//The tile offsets
		xOffset = 0, yOffset = 0;
		x = xOffset, y = yOffset;
	}


	//Open the map
	ifstream map("tiling/Hidden.map");

	//If the map couldn't be loaded
	if (!map.is_open())
	{
		cout << "Unable to load map file!\n";
		tilesLoaded = false;
	}
	else
	{
		int collectablesSetted = 0;
		int trophiesSetted = 0;
		//Initialize the tiles
		for (int i = 0; i < TOTAL_TILES; ++i)
		{
			//Determines what kind of tile will be made
			int tileType = -1;

			//Read tile from map file
			map >> tileType;
			//Determines teleport value of the tile
			int tileTeleportValue = 0;
			//If there was a problem in reading the map
			if (map.fail())
			{
				//Stop loading map
				cout << "Error loading map: Unexpected end of file!\n";
				tilesLoaded = false;
				break;
			}
			//Sets teleport value of the tile depending of the presets
			if (tileType == TILE_TELEPORT_START|| tileType == TILE_TELEPORT_FINISH)
			{
				if (x == gamePanelTilesParameters.w * 23 + xOffset && y == gamePanelTilesParameters.h * 21 + yOffset)
				{
					tileTeleportValue = 1;
				}
				else if (x == gamePanelTilesParameters.w * 23 + xOffset && y == gamePanelTilesParameters.h * 18 + yOffset)
				{
					tileTeleportValue = 2;
				}

			}
			if (tileType >= TILE_COLLECTABLE &&  tileType <  TILE_DEATH_TRAP) {

				if (collectablesSetted < MAX_COLLECTABLE_COUNT)
				{
					//Random collectables to be trophies or traps
					//Check if there are enough trophies, otherwise assign as trophy
					if ((rand() % 10) < 4 && (MAX_COLLECTABLE_COUNT - collectablesSetted> currentLevelCollectables - trophiesSetted))
					{
						//Set current collectable of current tile, default hemight, width and type 
						collectableSet[collectablesSetted] = Collectable(x + gamePanelTilesParameters.w / 2 - 10, y + gamePanelTilesParameters.h / 2, 20, 20, TILE_DEATH_TRAP);
						tileType -= TILE_COLLECTABLE;
						collectablesSetted++;
						
					}
					//Assign as trophy if there aren't enough
					else if (trophiesSetted <= currentLevelCollectables)
					{
						//Set current collectable of current tile, default height, width and type 
						collectableSet[collectablesSetted] = Collectable(x + gamePanelTilesParameters.w / 2 - 10, y + gamePanelTilesParameters.h / 2, 20, 20, TILE_COLLECTABLE);
						tileType -= TILE_COLLECTABLE;
						collectablesSetted++;
						trophiesSetted++;
					}
					else {
						//Set current collectable of current tile, default hemight, width and type 
						collectableSet[collectablesSetted] = Collectable(x + gamePanelTilesParameters.w / 2 - 10, y + gamePanelTilesParameters.h / 2, 20, 20, TILE_DEATH_TRAP);
						tileType -= TILE_COLLECTABLE;
						collectablesSetted++;
					}
					
					
				}

			}
			//Assign as death trap
			else if(tileType >=TILE_DEATH_TRAP )
			{
				if (collectablesSetted < MAX_COLLECTABLE_COUNT)
				{
					//Set current collectable of current tile, default height, width and type 
					collectableSet[collectablesSetted] = Collectable(x + gamePanelTilesParameters.w / 2 - 10, y + gamePanelTilesParameters.h / 2 - 10, 20, 20, TILE_DEATH_TRAP);
					tileType -= TILE_DEATH_TRAP;
					collectablesSetted++;
				}
					
				
			}
			//If the number is a valid tile number
			if ((tileType >= 0) && (tileType < TOTAL_TILE_SPRITES))
			{
				tileSet[i] = new Tile(x, y, tileType, tileTeleportValue, currentPanelConstantParameters);

			}
			else if (collectablesSetted >= MAX_COLLECTABLE_COUNT) {
				int i = 0 ;
			}
			//If it doesn't recognize the tile type or it's out of range
			
			else
			{
				//Stop loading map
				cout << ("Error loading map: Invalid tile type at %d!\n", i);
				tilesLoaded = false;
				break;
			}

			//Move to next tile spot
			x += gamePanelTilesParameters.w;

			//If we've gone too far horizontally 
			if (x >= gamePanelLevelParameters.w - xOffset)
			{
				//Moves back
				x = xOffset;

				//Moves to the next row
				y += gamePanelTilesParameters.h;
			}
		}
		//Sets tile clips in the array 
		if (tilesLoaded)
		{
			gTileClips[TILE_TELEPORT_FINISH].x = 0;
			gTileClips[TILE_TELEPORT_FINISH].y = 0;
			gTileClips[TILE_TELEPORT_FINISH].w = gamePanelTilesParameters.w;
			gTileClips[TILE_TELEPORT_FINISH].h = gamePanelTilesParameters.h;

			gTileClips[TILE_TELEPORT_START].x = 0;
			gTileClips[TILE_TELEPORT_START].y = gamePanelTilesParameters.h;
			gTileClips[TILE_TELEPORT_START].w = gamePanelTilesParameters.w;
			gTileClips[TILE_TELEPORT_START].h = gamePanelTilesParameters.h;

			gTileClips[TILE_BLUE].x = 0;
			gTileClips[TILE_BLUE].y = gamePanelTilesParameters.h *2;
			gTileClips[TILE_BLUE].w = gamePanelTilesParameters.w;
			gTileClips[TILE_BLUE].h = gamePanelTilesParameters.h;

			gTileClips[TILE_CENTER].x = gamePanelTilesParameters.w *2;
			gTileClips[TILE_CENTER].y = gamePanelTilesParameters.h;
			gTileClips[TILE_CENTER].w = gamePanelTilesParameters.w;
			gTileClips[TILE_CENTER].h = gamePanelTilesParameters.h;

			gTileClips[TILE_TOP].x = gamePanelTilesParameters.w *2;
			gTileClips[TILE_TOP].y = 0;
			gTileClips[TILE_TOP].w = gamePanelTilesParameters.w;
			gTileClips[TILE_TOP].h = gamePanelTilesParameters.h;

			gTileClips[TILE_TOPRIGHT].x = gamePanelTilesParameters.w *3;
			gTileClips[TILE_TOPRIGHT].y = 0;
			gTileClips[TILE_TOPRIGHT].w = gamePanelTilesParameters.w;
			gTileClips[TILE_TOPRIGHT].h = gamePanelTilesParameters.h;

			gTileClips[TILE_RIGHT].x = gamePanelTilesParameters.w *3;
			gTileClips[TILE_RIGHT].y = gamePanelTilesParameters.h;
			gTileClips[TILE_RIGHT].w = gamePanelTilesParameters.w;
			gTileClips[TILE_RIGHT].h = gamePanelTilesParameters.h;

			gTileClips[TILE_BOTTOMRIGHT].x = gamePanelTilesParameters.w *3;
			gTileClips[TILE_BOTTOMRIGHT].y = gamePanelTilesParameters.h *2;
			gTileClips[TILE_BOTTOMRIGHT].w = gamePanelTilesParameters.w;
			gTileClips[TILE_BOTTOMRIGHT].h = gamePanelTilesParameters.h;

			gTileClips[TILE_BOTTOM].x = gamePanelTilesParameters.w *2;
			gTileClips[TILE_BOTTOM].y = gamePanelTilesParameters.h *2;
			gTileClips[TILE_BOTTOM].w = gamePanelTilesParameters.w;
			gTileClips[TILE_BOTTOM].h = gamePanelTilesParameters.h;

			gTileClips[TILE_BOTTOMLEFT].x = gamePanelTilesParameters.w;
			gTileClips[TILE_BOTTOMLEFT].y = gamePanelTilesParameters.h *2;
			gTileClips[TILE_BOTTOMLEFT].w = gamePanelTilesParameters.w;
			gTileClips[TILE_BOTTOMLEFT].h = gamePanelTilesParameters.h;

			gTileClips[TILE_LEFT].x = gamePanelTilesParameters.w;
			gTileClips[TILE_LEFT].y = gamePanelTilesParameters.h;
			gTileClips[TILE_LEFT].w = gamePanelTilesParameters.w;
			gTileClips[TILE_LEFT].h = gamePanelTilesParameters.h;

			gTileClips[TILE_TOPLEFT].x = gamePanelTilesParameters.w;
			gTileClips[TILE_TOPLEFT].y = 0;
			gTileClips[TILE_TOPLEFT].w = gamePanelTilesParameters.w;
			gTileClips[TILE_TOPLEFT].h = gamePanelTilesParameters.h;

			gTileClips[TILE_TRIPPLESIDED_RIGHT].x = 0;
			gTileClips[TILE_TRIPPLESIDED_RIGHT].y = gamePanelTilesParameters.h *3;
			gTileClips[TILE_TRIPPLESIDED_RIGHT].w = gamePanelTilesParameters.w;
			gTileClips[TILE_TRIPPLESIDED_RIGHT].h = gamePanelTilesParameters.h;

			gTileClips[TILE_TRIPPLE_SIDED_BOTTOM].x = gamePanelTilesParameters.w;
			gTileClips[TILE_TRIPPLE_SIDED_BOTTOM].y = gamePanelTilesParameters.h *3;
			gTileClips[TILE_TRIPPLE_SIDED_BOTTOM].w = gamePanelTilesParameters.w;
			gTileClips[TILE_TRIPPLE_SIDED_BOTTOM].h = gamePanelTilesParameters.h;

			gTileClips[TILE_TRIPPLE_SIDED_LEFT].x = gamePanelTilesParameters.w *2;
			gTileClips[TILE_TRIPPLE_SIDED_LEFT].y = gamePanelTilesParameters.h *3;
			gTileClips[TILE_TRIPPLE_SIDED_LEFT].w = gamePanelTilesParameters.w;
			gTileClips[TILE_TRIPPLE_SIDED_LEFT].h = gamePanelTilesParameters.h;

			gTileClips[TILE_TRIPPLE_SIDED_TOP].x = gamePanelTilesParameters.w *3;
			gTileClips[TILE_TRIPPLE_SIDED_TOP].y = gamePanelTilesParameters.h *3;
			gTileClips[TILE_TRIPPLE_SIDED_TOP].w = gamePanelTilesParameters.w;
			gTileClips[TILE_TRIPPLE_SIDED_TOP].h = gamePanelTilesParameters.h;

			gTileClips[TILE_DUAL_SIDED_HORIZONTAL].x = 0;
			gTileClips[TILE_DUAL_SIDED_HORIZONTAL].y = gamePanelTilesParameters.h *4;
			gTileClips[TILE_DUAL_SIDED_HORIZONTAL].w = gamePanelTilesParameters.w;
			gTileClips[TILE_DUAL_SIDED_HORIZONTAL].h = gamePanelTilesParameters.h;

			gTileClips[TILE_DUAL_SIDED_VERTICAL].x = gamePanelTilesParameters.w;
			gTileClips[TILE_DUAL_SIDED_VERTICAL].y = gamePanelTilesParameters.h *4;
			gTileClips[TILE_DUAL_SIDED_VERTICAL].w = gamePanelTilesParameters.w;
			gTileClips[TILE_DUAL_SIDED_VERTICAL].h = gamePanelTilesParameters.h;
			
			gTileClips[TILE_FINISH].x = gamePanelTilesParameters.w *2;
			gTileClips[TILE_FINISH].y = gamePanelTilesParameters.h *4;
			gTileClips[TILE_FINISH].w = gamePanelTilesParameters.w;
			gTileClips[TILE_FINISH].h = gamePanelTilesParameters.h;
			
			gTileClips[TILE_QUADRUPLE_SIDED].x = gamePanelTilesParameters.w *3;
			gTileClips[TILE_QUADRUPLE_SIDED].y = gamePanelTilesParameters.h *4;
			gTileClips[TILE_QUADRUPLE_SIDED].w = gamePanelTilesParameters.w;
			gTileClips[TILE_QUADRUPLE_SIDED].h = gamePanelTilesParameters.h;

		
		}
	}

	//Closes the file
	map.close();

	//If the map was loaded fine
	return tilesLoaded;
}







void Game(SDL_Renderer* menuRenderer, SDL_Window* menuWindow, ConstantParameters currentConstantParameters)
{
	//Store current panel window and renderer
	gameRenderer = menuRenderer;
	gameWindow = menuWindow;
	//Get current panel resolution-dependent needed global parameters
	currentPanelConstantParameters = currentConstantParameters;
	gamePanelScreenDimensions = currentPanelConstantParameters.getScreenDimensions();
	gamePanelTilesParameters = currentPanelConstantParameters.getTileDimensions();
	gamePanelCharacterParameters = currentPanelConstantParameters.getCharacterDimensions();
	gamePanelLevelParameters = currentPanelConstantParameters.getLevelDimensions();
	characterTileParameters = currentPanelConstantParameters.getCharacterTileDimensions();



	//Determines previous pressed key 
	const Uint8* previousKey = NULL;
	//Determines previous destination of the character
	string previousDestination = "";
	
	//Start up SDL and create window
	int startOfTime = SDL_GetTicks();
	//Stores tiem of death of character
	int endTimer = 0;

	int shieldTimer = 0;

		//Load media
		if (!loadInGameMedia())
		{
			cout<<("Failed to load media!\n");
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
						Mix_HaltMusic();
						quit = true;
					}

				}

				//clears screen renderer
				SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 0);
				SDL_RenderClear(gameRenderer);


				//Determines current pressed key 
				const Uint8* currentKey = SDL_GetKeyboardState(NULL);
				//Stores current destination of the character
				string CharacterDestination;
				//Stores count of steps to be made during the current round
				int currentStepsTurn = 0;
				//If the character should move 
				bool characterMove = true;

				//Stores current count of scored collectables
				int currentRoundCollectablesChecked = 0;
				





				//Checks the destination for character to move 
				if (currentKey[SDL_SCANCODE_UP] | currentKey[SDL_SCANCODE_W]) 
				{
					
					CharacterDestination = "up";
				
				}
				else if (currentKey[SDL_SCANCODE_DOWN] | currentKey[SDL_SCANCODE_S])
				{
					
					CharacterDestination = "down";
					
				}
				else if (currentKey[SDL_SCANCODE_RIGHT] | currentKey[SDL_SCANCODE_D])
				{
					
					CharacterDestination = "right";
					
				}
				else if (currentKey[SDL_SCANCODE_LEFT] | currentKey[SDL_SCANCODE_A])
				{
					
					CharacterDestination = "left";
					
				}
				else 
				{
					CharacterDestination = "nowhere";
				}
				
				//If previously clicked key was the same, velocity = 2 
				if (currentKey == previousKey) {
					currentStepsTurn = 2;
					characterMove = true;
				}
				//Moves the character to nowhere 
				else if (CharacterDestination == "nowhere")
				{
					currentStepsTurn = 1;
					characterMove = false;
				}
				//Velocity = 1 movement
				else {
					currentStepsTurn = 1;
					characterMove = true;
				}
				//Character movement function
				if ( Player.getState() != dead && Player.getState()!= win )
				{
					for (int currentStepsMade = 1; currentStepsMade <= currentStepsTurn; currentStepsMade++)
					{

						Player.Move(CharacterDestination, tileSet, currentPanelConstantParameters, xOffset, yOffset);
						//Half the speed of the Player
						if (SDL_GetTicks() % 2 == 1) {
							for (int currentEnemy = 0; currentEnemy < MAX_ENEMIES; currentEnemy++)
							{
								aiEnemy[currentEnemy].Move(Player, tileSet, currentPanelConstantParameters, xOffset, yOffset);
							}


						}
						

						if (characterMove)
						{
							if (characterRealSteps < gamePanelTilesParameters.w / 4) {
								characterRealSteps++;
							}
							else {
								characterSteps++;
								characterRealSteps = 0;
							}

						}

					}
				}
				
				//Checks every collectable if it is collected 
				for (int currentCollectable = 0; currentCollectable < currentLevelCollectables; currentCollectable++)
				{
					if (!collectableSet[currentCollectable].Scored())
					{
				
						//Check if has been collected
						if (collectableSet[currentCollectable].Checked(Player))
						{
							//Check if it is trophy
							if (collectableSet[currentCollectable].Type() == TILE_COLLECTABLE) 
							{
							currentRoundCollectablesChecked++;
								Player.setState(shielded);
								shieldTimer = SDL_GetTicks();
								
							}
							//Check if it is a trap
							else if (collectableSet[currentCollectable].Type() == TILE_DEATH_TRAP)
							{
								Player.setLife(1);
								if (Player.getLife() <= 0) {
									endTimer = SDL_GetTicks();
									Player.setState(dead);
								}
							
								
							}
						}
						
						
						else 
						{
							
						}

					}
					//Count it if it has been already checked
					else if (collectableSet[currentCollectable].Scored() && collectableSet[currentCollectable].Type() == TILE_COLLECTABLE) 
					{
						currentRoundCollectablesChecked++;
					}
				}


				
			
				//Checks Character  current teleport state
				if (Player.getTeleportState() == 1 && Player.getTeleportFinished() == 0)
				{
					if (Player.getTeleportStarted() == 0)
					{

						Player.setTeleportStarted(1);
						playerTicks = SDL_GetTicks();
						teleportText = 1;
					}
					else if (Player.getTeleportStarted() != 0 && playerTicks + 3000 <= SDL_GetTicks())
					{

						playerTicks = 0;
						Player.Teleport(currentPanelConstantParameters);
						teleportText = 2;
						playerTicks = SDL_GetTicks();

					}
				}

				



			
				



				//Sets previously clicked key with the current key value 
				if (CharacterDestination == "nowhere") {
					previousKey = NULL;
					previousDestination = CharacterDestination;
				}
				else  
				{
					previousKey = currentKey;
					previousDestination = CharacterDestination;
				}




				//Sets current camera position relatively to the character
				SDL_Rect currentCharacterBox = Player.getDimensions();
				
				currentLevelCamera = setCamera(currentLevelCamera, currentCharacterBox);
				
			
				//Renders game field 
				for (int i = 0; i < TOTAL_TILES; ++i)
				{
					tileSet[i]->render(currentLevelCamera, gTileTexture, gameRenderer, gTileClips);
				}








				//Renders the enemies
				Player.Render(currentLevelCamera, gameRenderer);
				for (int currentEnemy= 0; MAX_ENEMIES > currentEnemy; currentEnemy++) {
					aiEnemy[currentEnemy].Render(currentLevelCamera, gameRenderer);
				}
				

				//Renders the collectables if they weren't scored
				for (int currentCollectable = 0; currentCollectable < MAX_COLLECTABLE_COUNT; currentCollectable++) {
					if (!collectableSet[currentCollectable].Scored() ) {
						collectableSet[currentCollectable].Render(gameRenderer, currentLevelCamera);
					}
				}








				//Render text before teleport
				if (teleportText == 1)
				{
					gPreTeleportTextTexture.render(int(gamePanelScreenDimensions.w / 2 - gPreTeleportTextTexture.getWidth() / 2), int(gamePanelScreenDimensions.h/5.4), gameRenderer);
				}
				//Render text after teleporting
				else if ((playerTicks + 3000 >= SDL_GetTicks()) && (Player.getTeleportFinished() == 1) && teleportText == 2)
				{
					//Render the after-teleport text  texture for Character 1 200 px to the right and 100px of the top (relatively to the 1920x1080 resolution)
					if (Player.getTeleportValue() == 1) {
						
						gTextAfterTeleport1Texture.render(currentLevelCamera.x + int(gamePanelScreenDimensions.w/5.4),   int(gamePanelScreenDimensions.h/5.4), gameRenderer);
					}
					else if (Player.getTeleportValue() == 2) {
						gTextAfterTeleport2Texture.render(currentLevelCamera.x + int(gamePanelScreenDimensions.w / 5.4), int(gamePanelScreenDimensions.h / 5.4), gameRenderer);
					}
					

				}
				//Resets teleport text 
				else if (playerTicks + 3000 <= SDL_GetTicks() && Player.getTeleportFinished() == 1 && teleportText == 2)
				{
					teleportText = 0;
					Player.setTeleportFinished(0);
				}





							
				//Visualize steps counter
				SDL_Color textColor = { 255,255, 255 };
				string stepsText = "Steps : " + to_string(characterSteps);
				stepsTextTexture.loadFromRenderedText(stepsText, textColor, gFont, gameRenderer);
				//Render the steps counter 1420 px to the left and 100 of the top (relatively to 1920x1080 resolution)
				stepsTextTexture.render(int(gamePanelScreenDimensions.w /1.35), int(gamePanelScreenDimensions.h /10.8), gameRenderer);

				string collectableText = "Trophies : " + to_string(currentRoundCollectablesChecked) + " / " + to_string(currentLevelCollectables);
				collectablesTextTexture.loadFromRenderedText(collectableText, textColor, gFont, gameRenderer);
				//Render the collectables centralized horizontally with negative offset of 200 px to the left  (relatively to 1920x1080 resolution)
				collectablesTextTexture.render(int(gamePanelScreenDimensions.w /2 - collectablesTextTexture.getWidth() - gamePanelScreenDimensions.w /9.6), int(gamePanelScreenDimensions.h / 10.8), gameRenderer);
				
				
				string timerText = "Timer : " + to_string(int(round(SDL_GetTicks() - startOfTime) /1000)) + " s";
				timerTextTexture.loadFromRenderedText(timerText, textColor, gFont, gameRenderer);
				//Render the collectables centralized horizontally with negative offset of 200 px to the left  (relatively to 1920x1080 resolution)
				timerTextTexture.render(int(gamePanelScreenDimensions.w / 2 - timerTextTexture.getWidth() - gamePanelScreenDimensions.w / 9.6), int(gamePanelScreenDimensions.h - gamePanelScreenDimensions.h / 10.8 - timerTextTexture.getHeight()/2), gameRenderer);

				
				textColor = { 153,0,0 };
				string lifeText = "Lifes : " + to_string(Player.getLife());
				lifesTextTexture.loadFromRenderedText(lifeText, textColor, gFont, gameRenderer);
				//Render the life text
				lifesTextTexture.render(int(gamePanelScreenDimensions.w / 2 + lifesTextTexture.getWidth() + gamePanelScreenDimensions.w / 9.6), int(gamePanelScreenDimensions.h - gamePanelScreenDimensions.h / 10.8 - lifesTextTexture.getHeight() / 2), gameRenderer);
				



				//Reset shield
				if (Player.getState() == shielded && (shieldTimer + 4000 <= SDL_GetTicks() && shieldTimer!= 0 ) ) 
				{
					Player.setState(alive);
					shieldTimer = 0;
				}


				//Check if the enemy caught the player
				for (int currentEnemy = 0; currentEnemy < MAX_ENEMIES; currentEnemy++)
				{
					if (Player.getState() != shielded && checkCollision(Player.getDimensions(), aiEnemy[currentEnemy].getDimensions()))
					{
						Player.setState(dead);

						if (endTimer == 0)
						{
							endTimer = SDL_GetTicks();
						}

					}
				}
				
			//Check if the game has ended
				 if((endTimer + 2000 <= SDL_GetTicks() && endTimer != 0) && (Player.getState() == dead || win) )
				{
					Mix_HaltMusic();
					SaveMenu(gameRenderer, gameWindow, currentConstantParameters, characterSteps, (SDL_GetTicks() - startOfTime) / 1000, currentRoundCollectablesChecked, Player.getState());
					quit = true;
					clearParameters();
				}

			//Check if the player checked all the trophies
				 if (currentLevelCollectables == currentRoundCollectablesChecked) {
					 if (endTimer == 0) {
						 endTimer = SDL_GetTicks();
					 }
					 else if (endTimer + 2000 <= SDL_GetTicks())
					 {
						 Player.setState(win);
					 }
				 }




				//Check if M key is pressed for sound modulation
				if (currentKey[SDL_SCANCODE_M])
				{
					if (stopMusic == 0) {
						stopMusic = 1;
					}
					else {
						stopMusic = 0;
					}
				}

				//Check if 3 seconds have been passed to play the music
				if (startOfTime + 3000 <= SDL_GetTicks()) {
					if (Mix_PlayingMusic() == 0 && stopMusic == 0) {
						Mix_PlayMusic(loudTetris, -1);
					}
					else if (Mix_PlayingMusic() == 1 && stopMusic == 1) {
						Mix_HaltMusic();
					}
				}
				else {
					//Render the sound alert texture at the middle horizontally and 100 px of the top(relatively to 1920x1080 resolution) vertically
					gSoundTexture.render(gamePanelScreenDimensions.w / 2 - gSoundTexture.getWidth(), int(gamePanelScreenDimensions.h /10.8*2), gameRenderer);
				}
				


				//Flickering announcement and function
				if (startOfTime + 20000 <= SDL_GetTicks() && startOfTime + 23000 >= SDL_GetTicks()) {

					textColor = {153,0,0 };
					LoadedTexture suddenlyWentDarkTexture;
					suddenlyWentDarkTexture.loadFromRenderedText("Suddenly all went dark!", textColor, gFont, gameRenderer);
					suddenlyWentDarkTexture.render(gamePanelScreenDimensions.w / 2 - suddenlyWentDarkTexture.getWidth() / 2, gamePanelScreenDimensions.h - gamePanelScreenDimensions.h / 10.8 * 2 - suddenlyWentDarkTexture.getHeight() / 2, gameRenderer);
				}
				else if (startOfTime + 23000 < SDL_GetTicks() && startOfTime + 26000 >= SDL_GetTicks() )
				{
					//Screen blackout
					SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 0);
					SDL_RenderClear(gameRenderer);
				}
				else if (startOfTime + 26000 < SDL_GetTicks()) {
					if (int random = rand() % 10 != 0) 
					{
						if (SDL_GetTicks() / random % 3 == 2)
						{
							//Screen black flickering
							SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 0);
							SDL_RenderClear(gameRenderer);
						}
					}
					
				}










				//Update screen
				SDL_RenderPresent(gameRenderer);
			

			
		}
	}

	//Free resources and close SDL


}


//Clear game parameters
void clearParameters() {
	xOffset, yOffset = 0;
	currentLevelCollectables = 0;
	characterSteps = 0;
	stopMusic = 0;
	teleportText = 0;
	enemyTicks = 0;
	playerTicks = 0;
	

}