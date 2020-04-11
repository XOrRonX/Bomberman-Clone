
/*
Class BaseObject

all the class functions are virtual 
the classes who inherit from BaseObject are Robot, Guard and Ghost
All the functions are implemented in those classes

*/


#pragma once
#include <SFML/Graphics.hpp>
#include "StaticObject.h"
#include "Bomb.h"

namespace sf {
	class Color;
	class RenderWindow;
}

class BaseObject
{
public:
	BaseObject() = default;
	virtual ~BaseObject() = default;
	
	virtual void draw(sf::RenderWindow& renderWindow) const = 0;
	virtual void move(const sf::Vector2f& vector2f,
					  const sf::Vector2f& screenBoundryMin,
					  const sf::Vector2f& screenBoundrymax,
					  sf::Vector2f rbotLocation) = 0;
	virtual void moveRevert() = 0;
	virtual void setToDefault() = 0;
	virtual unsigned int getState() const = 0;
	virtual bool isCollide(const sf::FloatRect& rect) const = 0;
	virtual bool collideHandler(BaseObject& baseObject) = 0;	
	virtual bool collideHandlerStatic(StaticObject& staticObject) = 0;
	virtual bool collideHandler(Bomb& bomb) = 0;
	virtual sf::Vector2f getPosition() const = 0;
	virtual unsigned int getType() const = 0;
	virtual void changeState() = 0;
	virtual void disable() = 0;
	virtual bool getIsAlive() const = 0;
	virtual void setSize(const sf::Vector2f& size) = 0;
	virtual void setPosition(const sf::Vector2f pos) = 0;
	virtual void changeGuardSpeed()=0;
	bool m_guardCollide;
};

