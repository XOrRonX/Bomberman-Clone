#include "Ghost.h"


#include "Guard.h"
#include "macros.h"
#include "Bomb.h"
#include <cmath>
#include "Ghostbomb.h"


Ghost::Ghost(const sf::Vector2f& size, const sf::Vector2f& pos,
	std::vector<sf::Texture>& textures)
	: m_rectangle(size), m_index(VGHOST), m_textures(textures)
{
	m_alive = true;
	m_randFrequency = GUARD_RAND_FREQUENCY;
	m_rectangle.setPosition(pos);
	m_originalPosition = pos;
	m_rectangle.setTexture(&m_textures[m_index]);
	m_rectangle.setOrigin(m_rectangle.getLocalBounds().width
		/ 2, m_rectangle.getLocalBounds().height / 2);
}

void Ghost::draw(sf::RenderWindow& renderWindow) const
{
	renderWindow.draw(m_rectangle);
}

void Ghost::move(const sf::Vector2f& vector2f,
	const sf::Vector2f& screenBoundryMin,
	const sf::Vector2f& screenBoundrymax,
	sf::Vector2f rbotLocation)
{
	m_speed--;
	if (m_speed > 0)
		return;
	m_speed = GUARD_SPEED;
	m_randFrequency--;

	float x, y;
	sf::Vector2f guardLocation;
	guardLocation = m_rectangle.getPosition();
	x = abs(guardLocation.x - rbotLocation.x);
	y = abs(guardLocation.y - rbotLocation.y);

	// move in the direction of the robot.
	// move up/down if the robot is more far away 
	// in that direction then in the right or left direction 
	if (y > x )
	{
		if (guardLocation.y > rbotLocation.y)
		{
			m_rectangle.move({ 0, NEG_PIXEL_MOVE });
			m_prevMove = { 0, POS_PIXEL_MOVE };
		}
		else
		{
			m_rectangle.move({ 0, POS_PIXEL_MOVE });
			m_prevMove = { 0, NEG_PIXEL_MOVE };
		}
	}
	else // move horizontaly in the direction of the robot
	{
		if (guardLocation.x > rbotLocation.x)
		{
			m_rectangle.move({ NEG_PIXEL_MOVE, 0 });
			m_prevMove = { POS_PIXEL_MOVE , 0 };
		}
		else
		{
			m_rectangle.move({ POS_PIXEL_MOVE , 0 });
			m_prevMove = { NEG_PIXEL_MOVE , 0 };
		}
	}

}

Ghost::~Ghost()
{
}

bool Ghost::collideHandler(Bomb& bomb)
{
	return bomb.isCollide(m_rectangle.getGlobalBounds());
}

bool Ghost::isCollide(const sf::FloatRect& rect) const
{
	return m_rectangle.getGlobalBounds().intersects(rect);
}

bool Ghost::collideHandler(BaseObject& baseObject)
{
	return baseObject.isCollide(m_rectangle.getGlobalBounds());
}


bool Ghost::collideHandlerStatic(StaticObject& staticObject)
{
	return false;
}

// returns the type of object gaurd/ghost/robot
unsigned int Ghost::getType() const
{
	return m_index;
}





