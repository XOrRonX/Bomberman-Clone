
#pragma once

// this class inherit from StaticObject
// this is a life present in the game, it adds one life to a Robot
// if collided with a Robot and then it disapear


#include "StaticObject.h"

class Life : public StaticObject
{
public:

	Life(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures, unsigned int index);
	~Life();

};