
#pragma once

// class Ghostbomb
// this class is of a bomb that is being put by a ghost
// the ghust is a gaurd that can move through walls 
// it runs after the Robot and it throw bombs on it
// this is an adition to the orginal definition of the project

#include "StaticObject.h"
#include "Bomb.h"

class Ghostbomb : public Bomb
{
public:
	Ghostbomb(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures, const unsigned int index);
	~Ghostbomb();

	unsigned int getState();
	void bombHandle() {};
	bool collideHandlerBomb(StaticObject& staticObject);
	unsigned int getType();

private:
	float m_time;
	sf::Time m_t;
	sf::Clock m_clock;
	unsigned int m_state;
	unsigned int m_type;
};


