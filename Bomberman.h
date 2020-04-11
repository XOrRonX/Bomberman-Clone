
/*

Class Bomberman
This class is managing the whole game 
it is not aware of the details of the game only of the screens and the
outcome of the next move of the screen. 
When a screen end it move to the next screen
Screen m_game[MAX_SCREENS] - this is array or Class Screen
unsigned int m_totalPoints - holds the total point from the last screen 
unsigned int m_numOfScreens - holds how many screean are there 
unsigned int m_activeScreen - holds which of the screens is active 
unsigned int m_lifeLeft - holds how mant lives the robot have

*/

//=============================include=======================================



#pragma once

#include "Screen.h"
#include "Robot.h"
#include "macros.h"

//===============================Class Bomberman============================

class Bomberman
{
public:
	Bomberman();
	~Bomberman();
	void addScreen(char ** matrix, unsigned int numOfLines,
		unsigned int numOfSteps);
	void printScreen() const;
	unsigned int nextMove(unsigned int robotMove);


private:

	// array of class Screens - each screen is playing one screen
	// in each moment only one screen is active 
	Screen m_game[MAX_SCREENS]; 

	// Total points of the game from the last screen
	// it is updated when a screen ends
	unsigned int m_totalPoints;

	// how many screens are there in the game
	unsigned int m_numOfScreens;

	// which of the screens is active 
	unsigned int m_activeScreen;

	// how many lives are left to the robot
	unsigned int m_lifeLeft;

	// called after a screen end and need to move to the next screen
	void moveToNextScreen();
};

