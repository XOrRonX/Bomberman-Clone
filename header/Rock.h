#pragma once

// this class inherit from StaticObject
// this is a Rock in the game, can be active or not if exploded 



#include "StaticObject.h"

class Rock : public StaticObject
{
public:
	Rock(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures, const unsigned int index);
	~Rock();

};

