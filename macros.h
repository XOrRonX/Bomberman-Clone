
/*
macros.h
hold all the varous enums and const from the program
*/

//====================================consts================================

#pragma once

// Maximum Robot life
const int MAX_LIFE = 3;

// Initialize point it is const in case there is need to 
// start with different number
const int POINTS_INIT = 0;

// maximum number of screen the game support
const int MAX_SCREENS = 20;

// the longest line in Board.txt is 256
const int MAX_LINE_SIZE = 256;

// the biggest screen to play has 80 lines and 80 columns
const int MAX_SCREEN_SIZE = 80;

// the basic bonus for a robot who finds a door * number of guards
const int DOOR_BONUS = 20;

// the basic bonus for a guard getting killes * number of guards
const int GUARD_BONUS = 5;

// Because each bomb explodes after 4 turns
// and a robot cannot put two bombs in the same place
// there are only 3 bombs that can be active at the same time
const int NUM_OF_BOMBS = 5;

// EASIEST and HRDEAST are how agressive is the guard in his move
// EASIEST means every 4 robot steps the guards are trying to move
// in the direction of the Robot and rest of the time it is doing
// a random move
// HARDEST is 1 which means every move the guards is trying to 
// get to the Robot 
const int EASIEST = 1;
const int HARDEST = 20;

//==================================enums=================================

// screen can have different states depending on what happened 
enum screenState {  ROBOT_KILLED_NO_STEPS = 1, 
					ROBOT_FOUND_DOOR = 2, 
					GAME_OVER = 3 ,
					GAME_WON = 4, 
					BOMB_KILLED_ROBOT = 5, 
					BOMB_KILLED_GUARD = 6,
					GUARD_KILLED_ROBOT = 7,
					NORMAL = 8, 
					CANT_MOVE = 9
				 };

// these are all the shapes that can be presented
// ERROR is happening when Robot or Guard try 
// to move outside the screen it is not a shape on the creen
enum shape { 
			 WALL = '#', 
			 ROCK = '@',  
			 ERROR = 'E', 
			 EXIT_DOOR = 'D', 
			 GUARD = '!',
	         EXPLODED = '*', 
			 ROBOT = '/', 
			 ROBOT_BOMB = '%', 
			 BOMB4 = '4',
			 BOMB3 = '3', 
			 BOMB2 = '2', 
			 BOMB1 = '1', 
			 SPACE = ' ' 
			};

// all the things a robot can do
enum robotMoves { 
				  UP = 1, 
				  DOWN = 2, 
				  LEFT = 3, 
				  RIGHT = 4, 
				  BOMB = 5, 
				  SKIP = 6,
				  HARDER = 7,
				  EASIER = 8
				};

enum locationType { 
					CURRENT_LOCATION = 1, 
					NEXT_LOCATION = 2, 
					ORIGINAL_LOCATION = 3 
				  };

