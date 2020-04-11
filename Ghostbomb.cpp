
#pragma once
#include "Ghostbomb.h"
#include "Bomb.h"
#include "macros.h"



Ghostbomb::Ghostbomb(const sf::Vector2f& size, const sf::Vector2f& pos,
	std::vector<sf::Texture>& textures, const unsigned int index) :
	Bomb(size, pos, textures, index)
{
	m_type = VGHOSTBOMB;
	m_clock.restart();
	m_state = BEFORE_EXPLODED;
}

unsigned int Ghostbomb::getState()
{
	
	return m_state;
}

bool Ghostbomb::collideHandlerBomb(StaticObject& staticObject)
{
	if (staticObject.getType() == VROCK)
		if (staticObject.isCollide(m_rectangle.getGlobalBounds()))
			return true;
	return false;
}
unsigned int Ghostbomb::getType()
{
	return m_type;
}

Ghostbomb::~Ghostbomb()
{

}