#include "Present.h"



Present::Present(const sf::Vector2f& size, const sf::Vector2f& pos,
	std::vector<sf::Texture>& textures, unsigned int index ) : 
	StaticObject(size, pos, textures, index)
{
}


Present::~Present()
{
}


