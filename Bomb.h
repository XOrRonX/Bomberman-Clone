
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

//==========================include======================================

#pragma once

#include "Vertex.h"


//========================Class Bomb====================================
class Bomb
{
public:
	Bomb();
	~Bomb();

	// constructor of the bomb with a location 
	Bomb(Vertex location);

	// initialize a bomb that exist 
	void initBomb(Vertex location);


	// each turn count down from 4 to 0
	// updating m_countDown
	void countDown();

	// returns true if m_active si true and
	// false if it is false
	bool isActive() const;

	// if m_shape == EXPLODED return true else false
	unsigned int isExploded() const;

	// check if loaction is equal to m_location.
	// returns true of equal and false if not
	bool isEqual(Vertex location) const;

	// Disable make m_active false
	void disable();

	// returns m_location of the bomb
	Vertex getLocation() const;

	// returns the current shape of the bomb
	char getShape() const;

private:

	//location of the bomb of class Vertex
	Vertex m_location;

	// count down 4-0 to explosion 
	unsigned int m_countDown;

	// current shape of the bomb getting update
	// every turm before it explodes 
	char m_shape;

	// true if the bomb is active and false if not
	bool m_active;
};

