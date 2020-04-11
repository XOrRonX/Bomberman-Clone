/*

Class Screen
This class is the main class of the game Bomberman
it is playing the game for one screen, it know all the rules of the game
and it has all the objects of the game:
Class Display m_display - a calss that hold the matrix of chars in size screen
Class Robot m_robot - this is the robot of the game 
Class Guard *m_guards - array of the guards of the screen
Class Bomb m_bombs[] - array of bombs for all the bombs that the robot put 

*/

//=============================includes=======================================

#pragma once

#include "Robot.h"
#include "Board.h"
#include "Guard.h"
#include "Bomb.h"
#include "Display.h"
#include <iostream>
#include "macros.h" 

//============================class Screen=====================================

class Screen
{
public:
	Screen();

	// constractor includes the data from the input file
	// and it also include the stage of that screen 0
	// mean it is the first screen
	Screen(char **screen, unsigned int size,
		   unsigned int steps, unsigned int stage);
	~Screen();

// Functions called externally from Bemberman 

	// prints the screen and the aditional info
	// calling the function printScreenInfo()
	void printScreen() const;

	// print number of point, number of life, stage
	// number of steps 
	void printScreenInfo() const;

	// the heart of Screen, managing every move for robot Guard and bomb 
	// its input is the move to make (UP/DOWN/RIGHT/LEFT/BOMB/SKIP)
	// its outout is the move and the new state of screen which is
	//defined in enum screenSate in macros.h
	void nextMove(unsigned int robotMove);

	// return the private variable m_points of Robot
	unsigned int getPoints() const;

	// set the private variable m_points of Robot
	// input is number of potins no output
	void setPoints(unsigned int totalPoints);

	// return the private variable m_lifeLeft of Robot
	// which holds the number of life left 
	unsigned int getLife() const;

	// set the private variable m_lifeLeft of Robot
	// which holds the number of life left 
	void setLife(unsigned int lifeToSet);

	// return the m_state of the Screen m_state holds the 
	// current state which can be one of all the states
	// in enum screenState in macros.h
	unsigned int getState() const;

	// User can decide to ask for more agressive move of guard.
	// at the easiest mode the guard is moving randomly every move
	// at the hardest mode the guard is chasing the Robot everymove
	void changeGuardAgressive(unsigned int key);


	
private:

//========================Data Structures of class Screen====================

	// hold the size of the screen (number of lines and columns)
	unsigned int m_screenSize;

	// The robot of the screen
	Robot m_robot;

	// arracy of guards 
	Guard *m_guards;

	// array of all the bombs the robot put in the screen
	Bomb m_bombs[NUM_OF_BOMBS];

	// holds the matrix of the screen with all the shapes
	Display m_display;

	// hold the state of the screen the state 
	// is defined in macros.h
	unsigned int m_state;

	// hold the stage of the game it is same as the number of the screen
	unsigned int m_stage;

	// hold how many guards are there in the screen
	unsigned int m_numOfGuards;

	// hold the total number of bombs the Robot put in the screen
	unsigned int m_numOfBombs;

	// how many steps the Robot have before he die and the screen reset
	// for each step this number is going down until it reach 0
	unsigned int m_numOfSteps;

	// Keep the original number of steps and is not changing 
	// it is needed so after the m_numOfSteps get to 0 it get 
	// the original number of steps 
	unsigned int m_originalNumOfStaps;

	//The door of the screen
	Vertex m_door;

	// level of difficulty refelct how agressive is the guard in 
	// chasing the robot
	unsigned int m_gameDifficulty;

//========================private functions of class Screen=================

	//=============take care of Robot nextMove=======================

	// Called from nextMove which is called by Bomberman
	// input: move that can be UP/DOWN/RIGHT/LEFT/BOMB/SKIP
	// output: execute the move and update screen state (m_state)
	void moveRobot(unsigned int robotMove);

	// get as input the next planned step of a robot
	// get the shape in that location from m_display and then decide 
	// what state the screen will be after the move.
	// called by moveRobot
	void getRobotNextMoveState(Vertex move);

	// after the move was set then need to update the current location 
	// and the next location
	void updateDiplayRobotMove();


	// in case robot finished its steps 
	//  need to get the screen to its orignal state
	void resetScreenNoSteps();


	// ==============take care of Guard next move===================


	// Called from nextMove which is called by Bomberman
	// input: which guard index in the m_gurads array to move
	// output: update the move and the screen state
	void moveGuard(unsigned int index);


	// get as input the next planned step of a Guard
	// get the shape in that location from m_display and then decide 
	// what state the screen will be after the move.
	void getGuardNextMoveState(Vertex move);

	// The algorithm to decide where to move the Guard
	// Gaurd movement - The guard movement has two parts to it:
	//  1. Tries to move closer to the Robot based on i and j
	//  2. Take a random step.
	// The decision if to do 1 or 2 above each step is dependant on 
	// m_gameDifficulty, the higher it is the less frequent the guard
	// take a random step. it also take a random step if the next step 
	// is blocked 
	// The user can get m_gameDifficulty up using the 'h' key
	// and down using the 'e' key - pressing these keys
	// do not count as moves or steps.
	Vertex whereToMoveGuard(unsigned int index);

	// Tries to get closer to the Robot called from whereToMoveGuard
	Vertex guardChaseRobot(unsigned int index);


	// after the move was set then need to update the current location 
	// and the next location of the Guard
	void updateDiplayGuardMove(unsigned int index);


	//====================update bomb each move if===================

	// Called from nextMove which is called by Bomberman
	// input: which guard index in the m_bombs array to update
	// output: update the screen using getBombShape
	// if exploded start the process of a bomb that exploded
	void updateBomb(unsigned int index);

	// returns the current shape of a bomb
	// to be displayed - called from updateBomb
	char getBombShape(Vertex bombLocation) const;

	// check no guard in location called by update bomb
	bool noGuardInLocation(Vertex location) const;

	//==========these functions take care of killing a robot by a guard======= 

	// take care of killing a robot 
	// then it calls reset robot and reset Guards 
	void handleKilledRobot();

	// reset robot is getting the robot to it original location 
	// it is also removing all bombs around the original location 
	// calling removeAllBombsAroundLocation
	void resetRobot();

	// Reset all Guards after a robot was killed moving them all to their 
	// original location 
	void resetGuards();

	// removing all bombs on the location and around the original location of the
	// robot for each bomb it find it call removeOneBomb
	void removeAllBombsAroundLocation(Vertex Location);

	//remove one bomb from a location 
	void removeOneBomb(Vertex location);


	//========all functions taking care of bob explosion====================

	//the main function that is starting all the process of bomb explosion
	void handleExplodedBomb(unsigned int index);

	// look for all the guards around an exploded bomb and kill them
	// for each guard it find it call bombKillGuardOnlocation 
	void bombKillAllGuardsAroundLocation(Vertex bombLocation);

	// kill one gaurd on a location 
	void bombKillGuardOnLocation(unsigned int index);

	// destory all ricks around the location of a bob that exploded 
	// for each rock it finds it call bombExplodeOneRock
	void bombExplodeAllRocksAroundLocation(Vertex bombLocation);

	// explode one rock in a location 
	void bombExplodeOneRock(Vertex bombLocation);

	// look for a robot around and exploded bomb 
	// if it finds then it call bombKillRobotdOnLocation
	// and then resetRobot
	void bombKillRobrtIfExist(Vertex bombLocation);

	//kill a robot if exist around an bomb that exploded 
	void bombKillRobotdOnLocation();
	
	// this function is drawing "shape" around a bomb
	// the two shapes are SPACE = ' ' or EXPLODED = '*'
	void bombDrawAround(Vertex bombLocation, char shape);

	
	
};

