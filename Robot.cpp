/*

Class Robot
This class is managing the Robot
it is not aware of the game only of itself
It has the following data strauctures:
m_image of class MovingImage which takes care of location management
unisgned int m_points holds the total points of the robot
unisgned int m_lifeLeft holds the number of life that are left
bool m_gameOver - becomes true after m_lifeLeft is 0

*/

//=============================include=======================================

#include "Robot.h"
#include "macros.h"
#include "Screen.h"

Robot::Robot()
{
}
Robot::~Robot()
{
}

Robot::Robot(Vertex location)
{  
	m_lifeLeft = MAX_LIFE;
	m_points = POINTS_INIT;
	m_gameOver = false;
	m_image = MovingImage(location);
}


unsigned int Robot::getPoints() const
{
	return m_points;
}


Vertex Robot::nextMove(unsigned int direction)
{
	return m_image.nextMove(direction);
}


void Robot::setPoints(unsigned int totalPoints)
{
	m_points += totalPoints;
}

void Robot::setLife(unsigned int lifeLeft)
{
	m_lifeLeft = lifeLeft;
}

void Robot::defaultLocation()
{
	m_image.getToOriginalLocation();
}

void Robot::killRobot()
{
	m_lifeLeft--;
	if (m_lifeLeft == 0)
		m_gameOver = true;
}

Vertex Robot::getLocation(unsigned int type) const
{
	return m_image.getLocation(type);
}


bool Robot::isGameOver() const
{
	return m_gameOver;
}


unsigned int Robot::getLife() const
{
	return m_lifeLeft;
}

void Robot::moveToNextLocation() 
{
	m_image.moveToNextLocation();
}