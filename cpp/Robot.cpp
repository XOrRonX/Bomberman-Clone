

#include "Robot.h"
#include "macros.h"
#include "StaticObject.h"
#include "Wall.h"
#include "Rock.h"
#include "Ghostbomb.h"
#include <SFML/Audio.hpp>


Robot::Robot(const sf::Vector2f& size,const sf::Vector2f& pos, 
	         std::vector<sf::Texture>& textures)
	         : m_rectangle(size), m_index(VROBOT), m_textures(textures)
{
	
	m_rectangle.setPosition(pos);
	m_originalPosition = pos;
	m_rectangle.setTexture(&m_textures[m_index]);
	m_rectangle.setOrigin(m_rectangle.getLocalBounds().width / 2, m_rectangle.getLocalBounds().height / 2);
	m_speed = ROBOT_SPEED;
}

void Robot::draw(sf::RenderWindow& renderWindow) const 
{
	renderWindow.draw(m_rectangle);
}

// The main Robot move function
// this function gets the move - veror2f
// the boundries of the screen so the robot do not exit screeen
// It does not use Robot location this input is used by ghost
// that is also a basicObject
void Robot::move(const sf::Vector2f& vector2f, 
				 const sf::Vector2f& screenBoundryMin,
				 const sf::Vector2f& screenBoundrymax,
					sf::Vector2f rbotLocation)
{
	// m_speed is setting how frquent the Robot will move 
	// m_speed for Robot is set to 1 so every call to 
	// Move robot the Robot move
	m_speed--;
	if (m_speed > 0)
		return;
	m_speed = ROBOT_SPEED;
	sf::Vector2f location;
	m_prevMove.x = vector2f.x  * -1;
	m_prevMove.y = vector2f.y  * -1;
	m_rectangle.move(vector2f);
	location = m_rectangle.getPosition();

	// check if the robot move take him outside the screen 
	// then revert the move
	if (!(location.x <= screenBoundrymax.x && location.x >= screenBoundryMin.x) ||
		!(location.y <= screenBoundrymax.y && location.y >= screenBoundryMin.y))
		moveRevert();
}

// go back on the last move 
void Robot::moveRevert()
{
	m_rectangle.move(m_prevMove);
}

// the state is the way for the Robot to communicate
// with the game that something happened it can be
// found a door, foind a present, got killed and so on
unsigned int Robot::getState() const 
{
	return m_state;
}


void Robot::setToDefault()
{
	m_rectangle.setPosition(m_originalPosition);
	m_rectangle.setScale({ 1, 1 });
}


bool Robot::isCollide(const sf::FloatRect& rect) const
{
	return m_rectangle.getGlobalBounds().intersects(rect);
}

bool Robot::collideHandler(BaseObject& baseObject)
{
	return baseObject.isCollide(m_rectangle.getGlobalBounds());
}

bool Robot::collideHandler(Bomb& bomb)
{
	return bomb.isCollide(m_rectangle.getGlobalBounds());
}

// each time this function called it checks if 
// there is a collision with the staticObject it got
// if there is a collision it handles
// the function return true if the Robot should not move forward
// meaning there was a collision and false if he should move 
// forward either there was not collision or it is OK to run 
// over that object - like it is OK for robot to run over Bomb
bool Robot::collideHandlerStatic(StaticObject& staticObject)
{
	// check if there is a collision with staticObject
	// if there is then depends on the type of the object
	// do different things 
	if (staticObject.isCollide(m_rectangle.getGlobalBounds()))
	{
		switch (staticObject.getType())
		{
		case VDOOR:
			m_state = ROBOT_FOUND_DOOR;
			return true; 
			break;
		case VPRESENT:
			m_state = ROBOT_FOUND_PRESENT;
			return true;
			break;
		case VBOMB:
			return false;
			break;
		case VROCK:
			// in case the rock is exploded can run over
			if (staticObject.isActive())
				return true;
			return false;
			break;
		case VLIFE:
			m_state = ROBOT_FOUND_LIFE;
			return true;
			break;
		}
		return true;
	}
	return false;
}


void Robot::setSize(const sf::Vector2f& size)
{
	m_rectangle.setSize(size);
}

void Robot::changeState()
{
	m_state = NORMAL;
}

sf::Vector2f Robot::getPosition() const
{
	sf::Vector2f location;
	location = m_rectangle.getPosition();
	return location;
}

void Robot::setPosition(sf::Vector2f pos)
{
	sf::Vector2f location;
	location = m_rectangle.getPosition();
	location.x += pos.x;
	location.y += pos.y;
	m_rectangle.setPosition(location);
}

// returns the type of object gaurd/ghost/robot
unsigned int Robot::getType() const
{
	return m_index;
}