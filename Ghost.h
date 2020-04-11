
// Class Ghost
// this class is not part of the definitoin of the project
// it is an adition of a guard that can move through walls
// this guard can put bombs and when it collide with a Robot 
// it puts bomb where the robot is trying to explode him


#pragma once


#include <SFML/Graphics.hpp>
#include "BaseObject.h"
#include "Guard.h"
#include "Door.h"
#include "macros.h"
#include "Ghostbomb.h"

class Ghost : public BaseObject
{
public:

	Ghost(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures);
	~Ghost();

	// draw the Ghost
	void draw(sf::RenderWindow& renderWindow) const override;

	// move the Ghost, the guard calculate in this function
	// where to move it is not using vector2f for that 
	void move(const sf::Vector2f& vector2f,
		const sf::Vector2f& screenBoundryMin,
		const sf::Vector2f& screenBoundrymax,
		sf::Vector2f rbotLocation) override;

	// return true if the Ghost and rect collide
	bool isCollide(const sf::FloatRect& rect) const override;

	// returns true of collide with baseObject
	bool collideHandler(BaseObject& baseObject) override;

	// returns true of collide with staticObject
	bool collideHandlerStatic(StaticObject& staticObject) override;

	// returns true of collide with bomb
	bool collideHandler(Bomb& bomb) override;

	
	unsigned int getState() const { return NORMAL; };
	bool getIsAlive() const { return true; };
	sf::Vector2f getPosition() const { return m_rectangle.getPosition(); };

	// returns the type of object gaurd/ghost/robot
	unsigned int getType() const override;

	// empty functions
	void setSize(const sf::Vector2f& size) {};
	void setPosition(const sf::Vector2f pos) {};
	void changeState() {};
	void setToDefault() {};
	void moveRevert() {};
	void disable() {};
	void changeGuardSpeed() {};

private:
	sf::RectangleShape m_rectangle;
	int m_index;
	std::vector<sf::Texture>& m_textures;
	sf::Vector2f m_originalPosition;
	sf::Vector2f m_prevMove;
	unsigned int m_randFrequency;
	bool m_alive;
	unsigned int m_speed = 2;
};

