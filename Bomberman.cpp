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

#include "Bomberman.h"
#include "macros.h"


// the default constructor is basic not touching screens
Bomberman::Bomberman()
{
	m_totalPoints = 0;
	m_numOfScreens = 0;
	m_activeScreen = 0;
	m_lifeLeft = 3;
}


Bomberman::~Bomberman()
{
}

// adds a screen each time there is a new screen 
void Bomberman::addScreen(char ** matrix,unsigned int numOfLines, 
								unsigned int numOfSteps)
{
	// calling Screen constructor
	m_game[m_numOfScreens] = Screen(matrix, numOfLines, numOfSteps, m_numOfScreens);
	m_numOfScreens++;
}

void Bomberman::printScreen() const
{
	m_game[m_activeScreen].printScreen();

}

// called from main for every move 
 unsigned int Bomberman::nextMove(unsigned int robotMove)
{
	unsigned int screenState;

	// in this function the next move of everything (robot, guard and all mobms)
	m_game[m_activeScreen].nextMove(robotMove);

	// after nextMove the state of the screen is changed 
	// the state that bomberman look at are only GAME_OVER 
	// which is robor killed 3 times or ROBOT_FOUND_DOOR which 
	// means the robot finshed the sceen with success
	screenState = m_game[m_activeScreen].getState();


	switch (screenState)
	{
	case GAME_OVER:
		return GAME_OVER;
		break;
	case ROBOT_FOUND_DOOR:
	{
		m_totalPoints = m_game[m_activeScreen].getPoints();
		m_lifeLeft = m_game[m_activeScreen].getLife();

		// if this is the last screen then the game is won
		if (m_activeScreen == m_numOfScreens - 1)
			screenState = GAME_WON;
		// if more screens move to next screen
		else
			moveToNextScreen();
		return screenState;
		break;
	}
	
	}
	return NORMAL;
}

 void Bomberman::moveToNextScreen()
 {
	 // active screen is the next one
	 m_activeScreen++;

	 // copy to the new screen the points from the previous screen
	 m_game[m_activeScreen].setPoints(m_totalPoints);

	 // copy to the new screen that robot lifes that are left
	 m_game[m_activeScreen].setLife(m_lifeLeft);

	 // print the new screen 
	 m_game[m_activeScreen].printScreen(); 
 }