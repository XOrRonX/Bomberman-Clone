#include "Life.h"
#include "macros.h"


Life::Life(const sf::Vector2f& size, const sf::Vector2f& pos,
	std::vector<sf::Texture>& textures, unsigned int index) :
	StaticObject(size, pos, textures, index)
{
	m_objectType = VLIFE;
}


Life::~Life()
{
}
