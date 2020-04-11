#include "Wall.h"
#include "macros.h"



Wall::Wall(const sf::Vector2f& size, const sf::Vector2f& pos,
	std::vector<sf::Texture>& textures, const unsigned int index) :
	StaticObject(size, pos, textures, index)
{
}



Wall::~Wall()
{
}

