
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

#pragma once

#include "Vertex.h"

//========================Class MovingImage==================================

class MovingImage
{
public:
	MovingImage();
	~MovingImage();

	//constructor using location 
	// it update all location memebers to be location
	MovingImage(Vertex location);

	// Input is which location to return 
	// it can be CURRENT_LOCATION, NEXT_LOCATION or ORIGINAL_LOCATION 
	// the fucntion return the requested location 
	Vertex getLocation(unsigned int type) const;

	// update m_location to be m_originalLocation 
	// after robot is dead it go back to orginal location 
	void getToOriginalLocation();

	// input is direction to go (up/down/left/right)
	// the function calculate the next location from the current location
	// the function returns the Vertex of next location not changing 
	// current location
	Vertex nextMove(unsigned int direction);

	// update m_location to be the same as m_nextLocation
	// this is doing the actual move 
	void moveToNextLocation();

	// input Vertex as the next location 
	// the function update m_nextLocation to be nextLocation
	void setNextLocation(Vertex nextLocation);

private:

	// current location 
	Vertex m_location;
	
	// original location 
	Vertex m_originalLocation;

	// next location 
	Vertex m_nextLocation;
};

