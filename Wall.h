#pragma once

// this class inherit from StaticObject
// this is a wall in the game, the simplest object 


#include "StaticObject.h"

class Wall : public StaticObject
{
public:
	Wall(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures, const unsigned int index);
	~Wall();
	
};

