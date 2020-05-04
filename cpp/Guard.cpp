
#include "Guard.h"
#include "macros.h"
#include <cmath>

Guard::Guard(const sf::Vector2f& size, const sf::Vector2f& pos,
	std::vector<sf::Texture>& textures)
	: m_rectangle(size), m_index(VGUARD), m_textures(textures)
{
	m_hard = false;
	m_guardCollide = false;
	int rndom = rand() % 4;
	rndom <= 2 ? m_smart = true : m_smart = false; 
	m_alive = true;
	m_randFrequency = GUARD_RAND_FREQUENCY;
	m_rectangle.setPosition(pos);
	m_originalPosition = pos;
	m_rectangle.setTexture(&m_textures[m_index]);
	m_rectangle.setOrigin(m_rectangle.getLocalBounds().width / 2, m_rectangle.getLocalBounds().height / 2);
}

void Guard::draw(sf::RenderWindow& renderWindow) const
{
	if (m_alive == true)
		renderWindow.draw(m_rectangle);
}

void Guard::move(const sf::Vector2f& vector2f,
				 const sf::Vector2f& screenBoundryMin,
				 const sf::Vector2f& screenBoundrymax,
					sf::Vector2f rbotLocation)
{
	if (m_alive)
	{
		// How fast to move
		// Robot is moving every call to function move
		// guard have two mode - slow move when m_hard is false
		// fast move like the robot when m_hard is true
		// the m_hard is controller through pushing the h/H key
		// pressing once you flip the status
		m_speed--;
		if (m_speed > 0)
			return;
		if (m_hard==false)
			m_speed = GUARD_SPEED;
		if (m_hard)
			m_speed = 1;
		m_randFrequency--;

		// the case of the not smart guard
		// all his moves are random
		if (m_smart == false)
		{
			/*if (m_guardCollide == true)
				m_guardCollide = false;*/
			// check if time to decide on a new random move
			if (m_randFrequency == 0)
			{
				// when to change the random next move
				// otherwise continue on the same track
				m_randFrequency = GUARD_RAND_FREQUENCY;
				switch ((rand() % 4) + 1)
				{
				case UP:
					m_rectangle.move({ 0, NEG_PIXEL_MOVE });
					m_prevMove = { 0, POS_PIXEL_MOVE };
					break;
				case DOWN:
					m_rectangle.move({ 0, POS_PIXEL_MOVE });
					m_prevMove = { 0, NEG_PIXEL_MOVE };
					break;
				case LEFT:
					m_rectangle.move({ NEG_PIXEL_MOVE, 0 });
					m_prevMove = { POS_PIXEL_MOVE , 0 };
					break;
				case RIGHT:
					m_rectangle.move({ POS_PIXEL_MOVE , 0 });
					m_prevMove = { NEG_PIXEL_MOVE , 0 };
					
					break;
				}
			}
			else // continue as last move
			{
				sf::Vector2f next;
				next.x = m_prevMove.x * -1;
				next.y = m_prevMove.y * -1;
				m_rectangle.move(next);
			}
		}

		// the case when the guard is smart 
		if (m_smart)
		{
			float x, y;
			sf::Vector2f guardLocation;
			guardLocation = m_rectangle.getPosition();
			x = abs(guardLocation.x - rbotLocation.x);
			y = abs(guardLocation.y - rbotLocation.y);

			// in case the path is free and no collision
			// move in the direction of the robot if the 
			// distance is bigger vertically move in the 
			// vertical direction 
			if (y > x && m_guardCollide == false)
			{
				if (guardLocation.y > rbotLocation.y )
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
			else // move horizontally if no collision 
			{
				if (m_guardCollide == false)
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

			// in case a collission go for randon steps
			if (m_guardCollide)
			{
				m_guardCollide = false;
				switch ((rand() % 4) + 1)
				{
				case UP:
					m_rectangle.move({ 0, NEG_PIXEL_MOVE });
					m_prevMove = { 0, POS_PIXEL_MOVE };
					break;
				case DOWN:
					m_rectangle.move({ 0, POS_PIXEL_MOVE });
					m_prevMove = { 0, NEG_PIXEL_MOVE };
					break;
				case LEFT:
					m_rectangle.move({ NEG_PIXEL_MOVE, 0 });
					m_prevMove = { POS_PIXEL_MOVE , 0 };
					break;
				case RIGHT:
					m_rectangle.move({ POS_PIXEL_MOVE , 0 });
					m_prevMove = { NEG_PIXEL_MOVE , 0 };
					break;
				}
			}
		}
		sf::Vector2f location;
		location = m_rectangle.getPosition();
		if (!(location.x <= screenBoundrymax.x && location.x >= screenBoundryMin.x) ||
			!(location.y <= screenBoundrymax.y && location.y >= screenBoundryMin.y))
				moveRevert();
	}

}

// go back on the last move
void Guard::moveRevert()
{
	m_rectangle.move(m_prevMove);
}

unsigned int Guard::getState() const
{
	return m_state;
}

bool Guard::collideHandler(Bomb& bomb)
{
	return bomb.isCollide(m_rectangle.getGlobalBounds());
}

void Guard::setToDefault()
{
	m_rectangle.setPosition(m_originalPosition);
	m_rectangle.setScale({ 1, 1 });
	m_alive = true;
}


bool Guard::isCollide(const sf::FloatRect& rect) const
{
	return m_rectangle.getGlobalBounds().intersects(rect);
}


bool Guard::collideHandler(BaseObject& baseObject)
{
	return baseObject.isCollide(m_rectangle.getGlobalBounds());
}


bool Guard::collideHandlerStatic(StaticObject& staticObject)
{
	if (staticObject.isCollide(m_rectangle.getGlobalBounds()))
	{
		switch (staticObject.getType())
		{
		case VDOOR:
		case VPRESENT:
		case VBOMB:
		case VLIFE:
			return false;
			break;
		case VROCK:
			if (staticObject.isActive())
				return true;
			return false;
			break;
		}
		return true;
	}
	return false;
}

// returns the type of object gaurd/ghost/robot
unsigned int Guard::getType() const
{
	return m_index;
}

void Guard::disable()
{
	m_alive = false;
}
	

bool Guard::getIsAlive() const
{
	return m_alive;
}

// change the from hard to easy and easy to hard
// this set how fast the Guards move it is set 
// through pressing the h key once
void Guard::changeGuardSpeed()
{
	if (m_hard == false)
		m_hard = true;
	else
		m_hard = false;
}