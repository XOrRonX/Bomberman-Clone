
/*

Class MovingImage
This class is managing location
it is not aware of the game or what is the image, it is only aware
of location of moving image.
It has the following data strauctures:
Vertex m_location - hold the current location
Vertex m_nextLocation - hold the next location
Vertex m_originalLocation - hold the original location set in the constractor

*/

//=========================================include============================

#include "MovingImage.h"
#include "macros.h"



MovingImage::MovingImage()
{
}


MovingImage::~MovingImage()
{
}


MovingImage::MovingImage(Vertex location)
{
	m_location.copy(location);
	m_nextLocation.copy(location);
	m_originalLocation.copy(location);
}

Vertex MovingImage::getLocation(unsigned int type) const
{
	switch (type)
	{
	case CURRENT_LOCATION:
		return m_location;
	case NEXT_LOCATION:
		return m_nextLocation;
	case ORIGINAL_LOCATION:
		return m_originalLocation;
	};
	return m_location;
}

void MovingImage::getToOriginalLocation()
{
	m_location.copy(m_originalLocation);
	m_nextLocation.copy(m_originalLocation);
	
}

// update m_nextLocation to reflect the next move 
// from this location with direction (up/down/left/right)
Vertex MovingImage::nextMove(unsigned int direction)
{
	m_nextLocation.copy(m_location);
	m_nextLocation.moveVertex(direction);
	return m_nextLocation;
}


void MovingImage::moveToNextLocation()
{
	m_location.copy(m_nextLocation);
}

void MovingImage::setNextLocation(Vertex nextLocation)
{
	m_nextLocation.copy(nextLocation);
}