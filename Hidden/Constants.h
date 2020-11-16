﻿#pragma once




//Tile constants
const int TOTAL_TILES = 648;
const int TOTAL_TILE_SPRITES = 20;
const int TOTAL_OBJECT_SPRITES = 20;

//The different tile sprites
enum tileTypes
{
	TILE_TELEPORT_FINISH,
	TILE_TELEPORT_START,
	TILE_BLUE,
	TILE_CENTER,
	TILE_TOP,
	TILE_TOPRIGHT,
	TILE_RIGHT,
	TILE_BOTTOMRIGHT,
	TILE_BOTTOM,
	TILE_BOTTOMLEFT,
	TILE_LEFT,
	TILE_TOPLEFT,
	TILE_TRIPPLESIDED_RIGHT,
	TILE_TRIPPLE_SIDED_BOTTOM,
	TILE_TRIPPLE_SIDED_LEFT,
	TILE_TRIPPLE_SIDED_TOP,
	TILE_DUAL_SIDED_HORIZONTAL,
	TILE_DUAL_SIDED_VERTICAL,
	TILE_FINISH,
	TILE_QUADRUPLE_SIDED,
	TILE_COLLECTABLE = 20,
	TILE_DEATH_TRAP = 40
};
//Character movement render states
enum characterMovementTypes
{
	CHARACTER_FORWARD_STEP_0,
	CHARACTER_FORWARD_STEP_1,
	CHARACTER_FORWARD_STEP_2,
	CHARACTER_FORWARD_STEP_3,
	CHARACTER_LEFTWARD_STEP_0,
	CHARACTER_LEFTWARD_STEP_1,
	CHARACTER_LEFTWARD_STEP_2,
	CHARACTER_LEFTWARD_STEP_3,
	CHARACTER_BACKWARD_STEP_0,
	CHARACTER_BACKWARD_STEP_1,
	CHARACTER_BACKWARD_STEP_2,
	CHARACTER_BACKWARD_STEP_3,
	CHARACTER_RIGHTWARD_STEP_0,
	CHARACTER_RIGHTWARD_STEP_1,
	CHARACTER_RIGHTWARD_STEP_2,
	CHARACTER_RIGHTWARD_STEP_3
	
	
	
	
};
//Enemy movement render states
enum enemyMovementTypes {

	ENEMY_FORWARD_STEP_0,
	ENEMY_FORWARD_STEP_1,
	ENEMY_FORWARD_STEP_2,
	
	ENEMY_LEFTWARD_STEP_0,
	ENEMY_LEFTWARD_STEP_1,
	ENEMY_LEFTWARD_STEP_2,
	
	ENEMY_BACKWARD_STEP_0,
	ENEMY_BACKWARD_STEP_1,
	ENEMY_BACKWARD_STEP_2,

	ENEMY_RIGHTWARD_STEP_0,
	ENEMY_RIGHTWARD_STEP_1,
	ENEMY_RIGHTWARD_STEP_2,
	

};

//Bool if the program is still running
const bool ProgramIsFinished = false; 
//Teleport presets for the character
enum teleportPresets {
	TELEPORT_PRESET_1,
	TELEPORT_PRESET_2
};



//Universal button states
enum buttonTypes {
	buttonNormal,
	buttonHighlighted,
	buttonPressed
};
//Character activity states
enum characterStates {
	shielded,
	alive,
	dead,
	win
};
//Enemy activity states
enum enemyStates {
	idle,
	chase
};

//Constant for maxmium player name size
const int MAX_PLAYER_NAME_WIDTH = 8;
const int MAX_COLLECTABLE_COUNT = 20;
const int MAX_ENEMIES = 8;
