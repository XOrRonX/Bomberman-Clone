
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

#include "Screen.h"
#include "macros.h"
#include <cstdio>
#include "Display.h"
#include <cstdio>

	//=====================Public Functions=================================


// Screen constructor

Screen::Screen()
{
}

Screen::~Screen()
{
}

Screen::Screen(char **screen, unsigned int size, unsigned int steps, 
				unsigned int stage)
{
	unsigned int guardIndex = 0;
	Vertex vertex;
	m_numOfBombs = 0;
	m_numOfGuards = 0;
	m_screenSize = size;
	m_state = NORMAL;
	m_stage = stage;
	m_numOfSteps = steps;
	m_originalNumOfStaps = steps;
	m_display = Display(screen, size);
	m_gameDifficulty = 20;

	for (unsigned int k  = 0 ; k < NUM_OF_BOMBS ; k++)
		m_bombs[k] = Bomb();

	// count guards in the screen to allocate the right array size
	m_numOfGuards = m_display.countChar(GUARD);

	// dynamically allocate the guards according to how many are found
	m_guards = new (std::nothrow) Guard[m_numOfGuards];
	if (m_guards == NULL)
	{
		std::cerr << "New failed\n";
		exit(EXIT_FAILURE);
	}

	// go over the matrix and look for robot and guards
	// for every guard found or robot call the constuctore
	// with the right location 
	for (unsigned int i = 0; i < size; i++)
	{
		for (unsigned int j = 0; j < size; j++)
		{
			switch(screen[i][j])
			{
			case ROBOT:
				vertex.m_i = i;
				vertex.m_j = j;
				m_robot = Robot(vertex);
				break;
			case GUARD:
				vertex.m_i = i;
				vertex.m_j = j;
				m_guards[guardIndex] = Guard(vertex);
				guardIndex++;
				break;
			case EXIT_DOOR:
				m_door.m_i = i;
				m_door.m_j = j;
				break;
			}
		}
	}
}

   //   Take care of printing screen and info


void Screen::printScreen() const
{
	m_display.printDisplay();
	printScreenInfo();
}


void Screen::printScreenInfo() const
{
	std::cout << "Total number of Points is: " << m_robot.getPoints() << "\n";
	std::cout << "Total number of life left is: " << m_robot.getLife() << "\n";
	std::cout << "Number of steps left is: " << m_numOfSteps << "\n";
	std::cout << "Number of stage is: " << m_stage << "\n";
	//std::cout << "Guard agressive is: " << m_gameDifficulty << "\n";
}



// the heart of Screen, managing every move for robot Guard and bomb 
// its input is the move to make (UP/DOWN/RIGHT/LEFT/BOMB/SKIP)
// its outout is the move and the new state of screen which is
// defined in enum screenSate in macros.h
void Screen::nextMove(unsigned int robotMove)
{
	m_state = NORMAL;

	// in case the user wants to change the guard agressiveness
	if (robotMove == HARDER || robotMove == EASIER)
	{
		changeGuardAgressive(robotMove);
		return;
	}

	// take care of robot move
	moveRobot(robotMove);
	if (m_state != NORMAL && m_state != SKIP)
		return;
	
	// Take care of all guards move
	for (unsigned int i = 0; i < m_numOfGuards; i++)
	{
		// do something only if guard is active 
		if (m_guards[i].isAlive())
		{
			m_state = NORMAL;
			moveGuard(i);
			if (m_state == GAME_OVER)
				return;
		}
	}

	// take care of all bombs
	for (unsigned int j = 0; j < NUM_OF_BOMBS; j++)
		if (m_bombs[j].isActive())
			updateBomb(j);

	m_display.setChar(EXIT_DOOR, m_door);
}

unsigned int Screen::getPoints() const
{
	return m_robot.getPoints();
}

void Screen::setPoints(unsigned int totalPoints)
{
	m_robot.setPoints(totalPoints);
}

unsigned int Screen::getLife() const
{
	return m_robot.getLife();
}

void Screen::setLife(unsigned int lifeToSet)
{
	m_robot.setLife(lifeToSet);
}


unsigned int Screen::getState() const
{
	return m_state;
}


  //=====================Private Functions=================================

// update the creen after the guard move - current and next location 
void Screen::updateDiplayGuardMove(unsigned int index)
{
	m_display.setChar(SPACE, m_guards[index].getLocation(CURRENT_LOCATION));
	char c = m_display.getChar(m_guards[index].getLocation(NEXT_LOCATION));
	m_display.setChar(GUARD, m_guards[index].getLocation(NEXT_LOCATION));
	m_guards[index].moveToNextLocation();

}


// take care of the next step of the guard
void Screen::moveGuard(unsigned int index)
{
	// get from the algorithm of guard move where it needs to move
	Vertex nextMove;
	nextMove.copy(whereToMoveGuard(index));

	// get information of what is the image in the nex move of the guard
	// it update the m_state of the screen
	getGuardNextMoveState(nextMove);
	// if next move cannot happen
	if (m_state == CANT_MOVE)
		return;

	// if next move is to a location where there is a robot
	if (m_state == GUARD_KILLED_ROBOT)
	{
		// kill the robot
		m_robot.killRobot();
		//if this was the 3rd kill of the robot then game is over
		if (m_robot.isGameOver())
			m_state = GAME_OVER;
		else
			// take care of everything related to kiiling a robot 
			// like reset the robot and the guards
			handleKilledRobot();
	}
	if (m_state == NORMAL)
		// if the move is good and no special case then just update the screen
		updateDiplayGuardMove(index);
}

Vertex Screen::guardChaseRobot(unsigned int index)
{
	Vertex nextMove, robotLocation, guardLocation;
	int vertDiff, horizDiff;
	
	nextMove = m_guards[index].getLocation(CURRENT_LOCATION);
	guardLocation = m_guards[index].getLocation(CURRENT_LOCATION);
	robotLocation = m_robot.getLocation(CURRENT_LOCATION);
	vertDiff = nextMove.verticalDifference(robotLocation);
	horizDiff = nextMove.horizontalDifference(robotLocation);

	// if the distance to the robot is higher on the vertical 
	// line then try to make progress in the vertical line
	if (abs(vertDiff) >= abs(horizDiff))
	{
		// if the robot is lower than the guard then go down
		if (vertDiff < 0)
			nextMove.m_i++;
		else
			nextMove.m_i--;
	}
	// if the distance to the robot is higher in the horizontal
	// line try to make progress in the horizontal line 
	else
	{
		// if the robot is on the right of the guard then go right
		if (horizDiff < 0)
			nextMove.m_j++;
		else
			nextMove.m_j--;
	}

	return nextMove;
}


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
Vertex Screen::whereToMoveGuard(unsigned int index)
{
	Vertex nextMove;
	int rndm;
	char shape;

	// guardChaseRobot is very agrresive in chasing the robot
	// in stage 0 we will use it slowly and in stage 1 more agressive 
	nextMove = guardChaseRobot(index);

	shape = m_display.getChar(nextMove);
	if (shape == WALL || shape == ERROR || shape == ROCK ||
		m_numOfSteps % m_gameDifficulty == 0)
	{
		rndm = (rand() % 4) + 1;
		nextMove = m_guards[index].getLocation(CURRENT_LOCATION);
		nextMove.moveVertex(rndm);
	}
	m_guards[index].setNextLocation(nextMove);
	return nextMove;
}

// update a bomb this function is called for each bomb that is active
void Screen::updateBomb(unsigned int index)
{
	Vertex location = m_bombs[index].getLocation();
	m_bombs[index].countDown();	
	// if the the count down caused the momb to be not active
	// it means that in the last trune the bomb exploded so now need 
	// to replace the '*' with ' ' 
	if (!m_bombs[index].isActive())
	{
		bombDrawAround(location, SPACE);
		return;
	}
	// if the count down got us to the time to explode the bomb
	// then take care of the bomb explosion 
	if (m_bombs[index].isExploded())
		handleExplodedBomb(index);
	// count down is still on going so need to update the screen
	else
	{
		if (m_robot.getLocation(CURRENT_LOCATION).isEqual(location))
			m_display.setChar(ROBOT_BOMB, location);
	      // if there is a guard in the bomb location then need to see the guard	
		if (noGuardInLocation(location) &&
			// and there is not robot in this location becuase if there is
			// need to show '%' and not the bomb shape
			!m_robot.getLocation(CURRENT_LOCATION).isEqual(location))
			m_display.setChar(m_bombs[index].getShape(), location);
	}
}

// killing the guard in m_guards[index]
void Screen::bombKillGuardOnLocation(unsigned int index)
{
	if (m_guards[index].isAlive())
	{
		m_guards[index].killGuard();

		// a guard was killed so need to update bonus points
		m_robot.setPoints(GUARD_BONUS * m_numOfGuards);
	}
}


// go over all guards and for each of them check if they
// are around a bomb that was just exploded it they are 
// then need to kill them 
void Screen::bombKillAllGuardsAroundLocation(Vertex bombLocation)
{
	Vertex nextLocation;

	// check the current location of an exploded bomb
	for (unsigned int k = 0 ; k < m_numOfGuards ; k++)
		if (bombLocation.isEqual(m_guards[k].getLocation(CURRENT_LOCATION)))
			bombKillGuardOnLocation(k);
	

	// for each guard look around the location of exploded bomb
	for (unsigned int i = 0 ; i < m_numOfGuards ; i++)
	{
		// look at all places around the exploded bomb
		for (unsigned int j = UP ; j <= RIGHT ; j++)
		{
			nextLocation.copy(bombLocation);

			// update the location to be up/down/right/left
			nextLocation.moveVertex(j);

			// if the guard is in that location kill him
			if (nextLocation.isEqual(m_guards[i].getLocation(CURRENT_LOCATION)))
				bombKillGuardOnLocation(i);
		}
	}
}

// clear one Rock that is in the exploded place
void Screen::bombExplodeOneRock(Vertex bombLocation)
{
	char shape = m_display.getChar(bombLocation);
	if (shape == ROCK)
		m_display.setChar(SPACE, bombLocation);
}


// loock around the bomb to see if there is a rock 
// if there is then remove it from the screen
void Screen::bombExplodeAllRocksAroundLocation(Vertex bombLocation)
{
	Vertex nextLocation;
	bombExplodeOneRock(bombLocation);
	for (unsigned int i = UP; i <= RIGHT; i++)
	{
		nextLocation.copy(bombLocation);
		nextLocation.moveVertex(i);
		bombExplodeOneRock(nextLocation);
	}
}


// kill a robot can cause game over if robot was killes 3 times
void Screen::bombKillRobotdOnLocation()
{
	m_robot.killRobot();
	if (m_robot.isGameOver())
		m_state = GAME_OVER;
	else
		handleKilledRobot();
}



// look around the exploded bomb to find a robot
void Screen::bombKillRobrtIfExist(Vertex bombLocation)
{
	Vertex nextLocation;

	if (bombLocation.isEqual(m_robot.getLocation(CURRENT_LOCATION)))
		bombKillRobotdOnLocation();

	for (unsigned int i = UP; i <= RIGHT; i++)
	{
		nextLocation.copy(bombLocation);
		nextLocation.moveVertex(i);
		if (nextLocation.isEqual(m_robot.getLocation(CURRENT_LOCATION)))
			bombKillRobotdOnLocation();
	}
}


// draw shape on bomb location and around it
// the shape can be '*' or ' '
void Screen::bombDrawAround(Vertex bombLocation, char shape)
{
	Vertex nextLocation;
	char nextShape;
	m_display.setChar(shape, bombLocation);
	for (unsigned int i = UP; i <= RIGHT; i++)
	{
		nextLocation.copy(bombLocation);
		nextLocation.moveVertex(i);
		nextShape = m_display.getChar(nextLocation);

		// do not draw if the location is a wall
		if (nextShape != WALL)
			m_display.setChar(shape, nextLocation);
	}

}


// the main fuunction that takes care of everything 
// that happen after a bomb is exploded 
void Screen::handleExplodedBomb(unsigned int index)
{
	Vertex bombLocation = m_bombs[index].getLocation();

	// kill all guards around
    bombKillAllGuardsAroundLocation(bombLocation);

	// remove all rocks around
	bombExplodeAllRocksAroundLocation(bombLocation);

	// kill robot if exist
	bombKillRobrtIfExist(bombLocation);

	// drow arounf the bomb the exploded sign '*'
	bombDrawAround(bombLocation,EXPLODED);
}


// get a location and check if there is any robot in a location 
// return true of there is a robot and flase if not
bool Screen::noGuardInLocation(Vertex location) const
{
	for (unsigned int i = 0; i < m_numOfGuards; i++)
	{
		if (m_guards[i].isAlive() && 
			location.isEqual(m_guards[i].getLocation(CURRENT_LOCATION)))
			return false;
	}
	return true;
}



// look at the next move a gaurd and update the sate
// after looking at what is in the location 
void Screen::getGuardNextMoveState(Vertex move)
{
	char figure = m_display.getChar(move);
	switch (figure)
	{
	case WALL:
	case ROCK:
	case ERROR:
		m_state = CANT_MOVE;
		break;
	case ROBOT:
		m_state = GUARD_KILLED_ROBOT;
		break;
	}
}


// look at the next move a gaurd and update the sate
// after looking at what is in the location 
void Screen::getRobotNextMoveState(Vertex move)
{
	char figure = m_display.getChar(move);
	switch (figure)
	{
	case WALL:
	case ROCK:
	case ERROR:
		m_state = CANT_MOVE;
		break;
	case EXIT_DOOR:
		m_state = ROBOT_FOUND_DOOR;
		m_robot.setPoints(DOOR_BONUS * m_numOfGuards);
		break;
	case GUARD:
		m_state = GUARD_KILLED_ROBOT;
		break;
	}
}


/*
moveRobot options
1. current location
	a. Is %
	b. Is /
2. Next Location
	a. is ' ' --> move robot 
	b. is Bomb --> change format of robot to %
	c. is Guard --> kill robot restart screen or game over
	f. number of steps == 0 --> kill robot restart screen renew steps or game over
	g. 'D' - end screen and move to next screen
*/

void Screen::moveRobot(unsigned int robotMove)
{
	Vertex move;
	m_state = NORMAL;
	if (robotMove == SKIP)
		m_state = SKIP;
	else 
	{
		if (robotMove == BOMB)
		{
			for (unsigned int j = 0; j < NUM_OF_BOMBS; j++)
				if (m_bombs[j].isEqual(m_robot.getLocation(CURRENT_LOCATION)) &&
					m_bombs[j].isActive())
					m_state = CANT_MOVE;

			if (m_state != CANT_MOVE)
			{
				m_bombs[m_numOfBombs].initBomb(m_robot.getLocation(CURRENT_LOCATION));
				m_display.setChar(ROBOT_BOMB, m_robot.getLocation(CURRENT_LOCATION));
				if (m_numOfBombs < NUM_OF_BOMBS - 1)
					m_numOfBombs++;
				else
					m_numOfBombs = 0;
				m_state = SKIP;
			}
		}
		else
		{
			move.copy(m_robot.nextMove(robotMove));
			getRobotNextMoveState(move);
		}
	}
	
	if (m_state != SKIP and m_state != CANT_MOVE)
	{
		if (m_numOfSteps == 0)
			m_state = ROBOT_KILLED_NO_STEPS;
		else
			m_numOfSteps--;
	}
	if (m_state == ROBOT_KILLED_NO_STEPS || /*m_state == BOMB_KILLED_ROBOT ||*/
		m_state == GUARD_KILLED_ROBOT)
	{
		if (m_state == ROBOT_KILLED_NO_STEPS)
			resetScreenNoSteps();
		m_robot.killRobot();
		if (m_robot.isGameOver())
			m_state = GAME_OVER;
		else
			handleKilledRobot();
	}
	if (m_state == NORMAL)
		updateDiplayRobotMove();
}


void Screen::resetScreenNoSteps()
{
	m_display.resetDisplayToOriginal();
	for (unsigned int i = 0; i < m_numOfGuards; i++)
		m_guards[i].getGuardToLife();
	for (unsigned int j = 0; j < NUM_OF_BOMBS; j++)
		m_bombs[j].disable();
}



// take care on how to kill a robot
// there is special case when the robot is killed
// because number of steps got to 0
void Screen::handleKilledRobot()
{
	if (m_state == ROBOT_KILLED_NO_STEPS)
		m_numOfSteps = m_originalNumOfStaps;
	resetRobot();
	resetGuards();
	//printScreen();
}



// get the robot to its orginal location 
void Screen::resetRobot()
{
	char c = m_display.getChar(m_robot.getLocation(CURRENT_LOCATION));
	if (c == ROBOT_BOMB)
	{
		char shape = getBombShape(m_robot.getLocation(CURRENT_LOCATION));
		m_display.setChar(shape, m_robot.getLocation(CURRENT_LOCATION));
	}
	if (c == ROBOT)
		m_display.setChar(SPACE, m_robot.getLocation(CURRENT_LOCATION));
	c = m_display.getChar(m_robot.getLocation(ORIGINAL_LOCATION));
	
	//remove all bombs on location or around location of the 
	//original location of the Robot
	removeAllBombsAroundLocation(m_robot.getLocation(ORIGINAL_LOCATION));
	m_display.setChar(ROBOT, m_robot.getLocation(ORIGINAL_LOCATION));
	
	// update the robot to move to his original location 
	m_robot.defaultLocation();
}


//check a location if there is a bomb then return its shape
// if not then return space
char Screen::getBombShape(Vertex bombLocation ) const
{ 
	for (unsigned int j = 0; j < NUM_OF_BOMBS; j++)
	{
		if (m_bombs[j].isEqual(bombLocation))
			return m_bombs[j].getShape();
	}
	return ' ';
}


// if there is bomb in location disable it 
void Screen::removeOneBomb(Vertex location)
{
	for (unsigned int j = 0; j < NUM_OF_BOMBS; j++)
	{
		if (m_bombs[j].isEqual(location))
			return m_bombs[j].disable();
	}
}


// disable all bombs on a location and around a location 
// it is called when there is a need to remove all bombs
// around the original location of a robot
void Screen::removeAllBombsAroundLocation(Vertex location)
{
	Vertex nextLocation;

	removeOneBomb(location);
	for (unsigned int i = UP; i <= RIGHT; i++)
	{
		nextLocation.copy(location);
		nextLocation.moveVertex(i);
		removeOneBomb(nextLocation);
	}
}

// get a guard to its original location 
void Screen::resetGuards()
{
	for (unsigned int i = 0; i < m_numOfGuards; i++)
	{
		if (m_guards[i].isAlive())
		{
			char c = m_display.getChar(m_guards[i].getLocation(CURRENT_LOCATION));
			m_display.setChar(' ', m_guards[i].getLocation(CURRENT_LOCATION));
			c = m_display.getChar(m_guards[i].getLocation(ORIGINAL_LOCATION));
			m_display.setChar(GUARD, m_guards[i].getLocation(ORIGINAL_LOCATION));
			m_guards[i].defaultLocation();
		}
	}
}

// after a robot move update display on current and next location 
void Screen::updateDiplayRobotMove()
{
	char c = m_display.getChar(m_robot.getLocation(CURRENT_LOCATION));
	if (c == ROBOT_BOMB)
	{
		char shape = getBombShape(m_robot.getLocation(CURRENT_LOCATION));
		m_display.setChar(shape, m_robot.getLocation(CURRENT_LOCATION));
	}
	if (c == ROBOT)
		m_display.setChar(SPACE, m_robot.getLocation(CURRENT_LOCATION));
	c = m_display.getChar(m_robot.getLocation(NEXT_LOCATION));

	// if in next locaiton there was a bomb then update it to be %
	if (c == BOMB4 || c == BOMB3 || c == BOMB2 || c == BOMB1)
		m_display.setChar(ROBOT_BOMB, m_robot.getLocation(NEXT_LOCATION));
	m_display.setChar(ROBOT, m_robot.getLocation(NEXT_LOCATION));
	m_robot.moveToNextLocation();
}


void Screen::changeGuardAgressive(unsigned int key)
{

	if ((key == HARDER) && (m_gameDifficulty < HARDEST))
		m_gameDifficulty++;
	if ((key == EASIER) && (m_gameDifficulty > EASIEST))
		m_gameDifficulty--;
}


