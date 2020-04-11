#pragma once

// this class inherit from StaticObject
// this is a present in the game, it adds one bomb if collided 
// with a Robot and then it disapear


#include "StaticObject.h"

class Present : public StaticObject
{
public:

	Present(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures, unsigned int index);
	~Present();

};

