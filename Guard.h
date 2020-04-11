
/*

Class Guard
This class is managing a Guard
it is not aware of the game only of itself
It has the following data strauctures:
m_image of class MovingImage which takes care of location management
bool m_isAliva a Robot can be alive or dead when did it is not doing anything

*/

//=============================include=======================================

#pragma once

#include "Vertex.h"
#include "MovingImage.h"


//============================Class Guard=====================================

class Guard
{
public:
	Guard();
	~Guard();

	//constructor, update the guard current, next and original location 
	// to be location and the m_alive to be true
	Guard(Vertex location);

	// input is direction to go (up/down/left/right)
	// the function is calling member of m_image to
	// calculate the next location from the current location
	// the function returns the Vertex of next location
	Vertex nextMove(unsigned int direction);

	// returns m_alive true if alive false if dead
	bool isAlive() const;

	// changes m_alive to be false 
	void killGuard();

	// input is which location to return can be current, next or original
	// output is the location that was requests
	Vertex getLocation(unsigned int location) const;

	// move current location to next location 
	void moveToNextLocation();

	// Get the robot to original location 
	// happen after a robot is dead 
	void defaultLocation();

	// set m_image next location to be the same as the input
	void setNextLocation(Vertex nextLocation);

	//return Guard to life for screen reset 
	void getGuardToLife();

private:

	// class MovingImage take care of all the movement betwen current
	// next and original locations.
	MovingImage m_image;

	// when Gaurds is dead m_alive will be changed to false
	bool m_alive;
};

