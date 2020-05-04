
/*

Class Robot
This class is managing the Robot
it inherits from the virtual class BaseObject 

*/

//=============================include=======================================

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "BaseObject.h"
#include "Guard.h"
#include "Door.h"
#include "Bomb.h"

//==========================Class Robo==============================

class Robot : public BaseObject
{
public:
	
	//constractor with location 
    Robot(const sf::Vector2f& size, const sf::Vector2f& pos, 
			std::vector<sf::Texture>& textures);
	
	// draws the Robot
	void draw(sf::RenderWindow& renderWindow) const override;

	// move the robot gets the vector to move and boundries of the 
	// screen to make sure it is not going outside the screen
	void move(const sf::Vector2f& vector2f, 
			  const sf::Vector2f& screenBoundryMin,
		      const sf::Vector2f& screenBoundrymax,
				sf::Vector2f rbotLocation) override;

	// used if the last move was wrong then move back to before the
	// last move
	void moveRevert() override;

	// returns the state of the Robot - found a door, killed by a guard
	// and so on
	unsigned int getState() const override;

	// Return the Robot to its original location and state
	void setToDefault() override;

	// return true if the roboot and rect collide
	bool isCollide(const sf::FloatRect& rect) const override;

	// handle a collision between a robot and guard
	bool collideHandler(BaseObject& baseObject) override;

	// handle a collision between a robot and a rock, wall, present,
	// life, door
	bool collideHandlerStatic(StaticObject& staticObject) override;

	// handle when the robot collide with a bomb
	bool collideHandler(Bomb& bomb) override;

	// chnage the size of the robot
	void setSize(const sf::Vector2f& size) override;
	
	// always return true that the robot is alive
	bool getIsAlive() const { return true; };

	// set Robot state to Normal 
	void changeState() override;

	// set the Robot to be in position pos
	void setPosition(sf::Vector2f pos) override;
	
	// returns the current Robot position 
	sf::Vector2f getPosition() const override;

	unsigned int getType() const override;


	// empty functions in robot
	void disable() {};
	void changeGuardSpeed() {};

private:
	
	sf::RectangleShape m_rectangle;
	int m_index;
	std::vector<sf::Texture>& m_textures;
	sf::Vector2f m_originalPosition;
	sf::Vector2f m_prevMove;
	unsigned int m_state = NORMAL;
	unsigned int m_speed = 1;
};

