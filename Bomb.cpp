/*

Class Bomb
This class is managing the Bomb
it is not aware of the game only of itself
It has the following data strauctures:
Vertex m_location -- location of the bomb - bomb is not moving
unsigned int m_countDown -- count down from 4 to 0 then explode
char m_shape -- the shape of the bomb changing with the count down
bool m_active -- if not acitve then the bomb is disabled
*/

//===================================include===============================

#include "Bomb.h"
#include "macros.h"



Bomb::~Bomb()
{
}
	

Bomb::Bomb()
{
	m_countDown = 5;
	m_shape = BOMB4;
	m_active = false;
}

void Bomb::initBomb(Vertex location)
{
	m_location.copy(location);
	m_countDown = 5;
	m_active = true;
	m_shape = BOMB4;

}



unsigned int Bomb::isExploded() const
{
	if (m_shape == EXPLODED)
		return true;
	return false;
}

bool Bomb::isActive() const
{
	return m_active;
}


void Bomb::countDown()
{
	
	switch (m_countDown)
	{ 
	case 5: // because count down appen after the case 
		m_shape = BOMB4;  
		break;
	case 4:
		m_shape = BOMB3;
		break;
	case 3:
		m_shape = BOMB2;
		break;
	case 2:
		m_shape = BOMB1;
		break;
	case 1:
		m_shape = EXPLODED;
		break;
	case 0:
		m_active = false; //disable the bomb
		m_shape = SPACE; // uodate its sape to be SPACE
		break;
	}
	if (m_countDown > 0)
		m_countDown--;

}

bool Bomb::isEqual(Vertex location) const
{
	return m_location.isEqual(location);
}

// this is called when need to clear all bombs
// around the original location of the roboto after 
// it is killed
void Bomb::disable()
{
	m_active = false;
	m_shape = SPACE;
	m_countDown = 0;
}



Vertex Bomb::getLocation() const
{
	return m_location;
}

char Bomb::getShape() const
{
	return m_shape;
}