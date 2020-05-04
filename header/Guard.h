
/*

Class Guard
This class is managing the Guard
it is inheriting from the abstruct class BaseObject

*/

//=============================include=======================================

#pragma once


#include <SFML/Graphics.hpp>
#include "BaseObject.h"
#include "Guard.h"
#include "Door.h"
#include "macros.h"
#include "Ghostbomb.h"

class Robot;
class Door;

//==========================Class Robo==============================

class Guard : public BaseObject
{
public:
	 
	Guard(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures);
	
	void draw(sf::RenderWindow& renderWindow) const override;

	// move the guard, the guard calculate in this function
	// where to move it is not using vector2f for that 
	void move(const sf::Vector2f& vector2f,
			  const sf::Vector2f& screenBoundryMin,
			  const sf::Vector2f& screenBoundrymax,
				sf::Vector2f rbotLocation) override;

	// if last move was not good - like collide with a rock
	// move back 
	void moveRevert() override;

	// returns the state of the Guard
	unsigned int getState() const override;

	// put the Guard in its defalt state and location 
	void setToDefault() override;

	// return true if the Guard and rect collide
	bool isCollide(const sf::FloatRect& rect) const override;

	// returns true of collide with baseObject
	bool collideHandler(BaseObject& baseObject) override;

	// returns true of collide with staticObject
	bool collideHandlerStatic(StaticObject& staticObject) override;

	// returns true of collide with bomb
	bool collideHandler(Bomb& bomb) override;

	// disable a Guard
	void disable();

	// change the Guard speed from its current speed to next
	// slow to fast or fast to slow
	void changeGuardSpeed();

	// returns the position of the Guard
	sf::Vector2f getPosition() const { return m_rectangle.getPosition(); };

	// returns true of the Guard is a live
	bool getIsAlive() const ;

	// returns the type of object gaurd/ghost/robot
	unsigned int getType() const override;

	// empty functions 
	void changeState() {};
	void setSize(const sf::Vector2f& size) {};
	void setPosition(sf::Vector2f pos) {};
	

private:
	
	// the frequency of Guard move by default is slower than robot
	unsigned int m_speed = 2;
	sf::RectangleShape m_rectangle;
	int m_index;
	std::vector<sf::Texture>& m_textures;
	sf::Vector2f m_originalPosition;
	sf::Vector2f m_prevMove;
	// for Guard that move in ramdom direction continue 
	unsigned int m_randFrequency;
	unsigned int m_state = NORMAL;
	sf::Vector2f m_guardRestart;
	bool m_alive;
	bool m_smart;  // is the Guard smart or not
	bool m_moveRevert;
	bool m_hard;  // is the Guard speed is fast or not 
};

