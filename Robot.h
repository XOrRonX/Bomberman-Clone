
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

#pragma once

#include "Vertex.h"
#include "Board.h"
#include "MovingImage.h"

//==========================Class Robo==============================

class Robot
{
public:
	Robot();
	~Robot();
	//constractor with location 
	Robot(Vertex location);

	// returns m_points - the number of points of the robot
	unsigned int getPoints() const;

	// input is direction to go (up/down/left/right)
	// the function is calling member of m_image to
	// calculate the next location from the current location
	// the function returns the Vertex of next location
	Vertex nextMove(unsigned int direction);

	// reduce the m_lifeLeft and update m_gameOver if needed
	void killRobot();

	// input is which location to return can be current, next or original
	// output is the location that was requests
	Vertex getLocation(unsigned int type) const;

	// returns m_gameOver;
	bool isGameOver() const;

	// returns m_lifeLeft - how many lifes are left to the Robot
	unsigned int getLife() const;

	// When moving between screens
	// need to update the Robot of the next screen
	// with the points from the Robot from the previos screen
	void setPoints(unsigned int totalPoints);

	// when moving between screens need to update
	// the next screen with the life that left for the robot
	// from the previous screen
	void setLife(unsigned int lifeLeft);

	// Get the robot to original location 
	// happen after a robot is dead 
	void defaultLocation();

	// move current location to next location 
	void moveToNextLocation();

private:

	// initialized to 3 life ad every time a robot is killed
	// it lose one life after the 3 kill the game end
	unsigned int m_lifeLeft;

	// keeps all the points the robot got in the screen
	// it also get the points from the previous screen
	unsigned int m_points;

	// if flase game is over and it is when the robot killes 3 times
	bool m_gameOver;

	// class MovingImage take care of all the movement betwen current
	// next and original locations.
	MovingImage m_image;

};

