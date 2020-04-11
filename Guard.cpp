/*

Class Guard
This class is managing a Guard
it is not aware of the game only of itself
It has the following data strauctures:
m_image of class MovingImage which takes care of location management
bool m_isAliva a Robot can be alive or dead when did it is not doing anything

*/

//=============================include=======================================

#include "Guard.h"
#include "macros.h"

Guard::Guard()
{
}


Guard::~Guard()
{
}

// constructore call MovingImage constructor with location 
Guard::Guard(Vertex location)
{
	m_image = MovingImage(location);
	m_alive = true;
}

void Guard::moveToNextLocation()
{
	m_image.moveToNextLocation();
}

void Guard::getGuardToLife()
{
	m_alive = true;
}

void Guard::setNextLocation(Vertex nextLocation)
{
	m_image.setNextLocation(nextLocation);
}

Vertex Guard::nextMove(unsigned int direction)
{
	return m_image.nextMove(direction);
}

bool Guard::isAlive() const
{
	return m_alive;
}

void Guard::killGuard()
{	
	m_alive = false;
}

Vertex Guard::getLocation(unsigned int location) const
{
	return m_image.getLocation(location);
}

void Guard::defaultLocation()
{
	m_image.getToOriginalLocation();
}