#include "Bomb.h"
#include "macros.h"
#include <SFML/Audio.hpp>

//creating a bomb and start the time down
Bomb::Bomb(const sf::Vector2f& size, const sf::Vector2f& pos,
	std::vector<sf::Texture>& textures, const unsigned int index) :
	StaticObject(size, pos, textures, index)
{
	if (!soundBufferExplosion.loadFromFile("Explosion+5.wav"))
		return;
	soundExplosion.setBuffer(soundBufferExplosion);
	if (!soundBufferBeep.loadFromFile("beep-21.wav"))
		return;
	soundBeep.setBuffer(soundBufferBeep);
	m_clock.restart();
	m_state = BEFORE_EXPLODED;
}

void Bomb::bombHandle()
{
	sf::Vector2f size;
	sf::Vector2f change;
	change = m_rectangle.getPosition();
	change.x = change.x - 5;
	change.y = change.y - 5;
	m_t = m_clock.getElapsedTime();
	m_time = m_t.asSeconds();

	switch (m_state)
	{
	case BEFORE_EXPLODED:
		if (m_time >= 1 )  // show the count down after a second
			updatePicture(V3);
		if (m_time >= 2 )
			updatePicture(V2);
		if (m_time >= 3)
		{
			updatePicture(V1);
			soundBeep.play();
		}
		// 4 second passed so explode but go in here only once
		if ((m_time >= 4) && (m_state != DURING_EXPLODED))
		{
			// creating a new shape because changing the 
			// existing one did not work well
			sf::RectangleShape rectangle;
			sf::Texture texture;
			rectangle.setPosition(m_rectangle.getPosition());
			texture.loadFromFile("exploded.gif");
			rectangle.setTexture(&texture);
			rectangle.setOrigin(m_rectangle.getLocalBounds().width / 2, m_rectangle.getLocalBounds().height / 2);
			// increase the size for the explosion to hit everything 
			// around that place
			rectangle.setSize({ 45 , 50 });
			m_rectangle = rectangle;
			// change the picture to explosion 
			updatePicture(VEXPLODED);
			soundExplosion.play();
			m_state = DURING_EXPLODED;
			m_rectangle.setPosition(change);
		}
		break;
	case DURING_EXPLODED:
		if (m_time >= 5) // the exploded bomb is effective a second
		{
			disable();
			m_state = AFTER_EXPLODED;
		}
		break;
	case AFTER_EXPLODED:
		break;
	}

	
}

unsigned int Bomb::getState()
{
	return m_state;
}


// The only static object impacted by bomb is Rock
// so check if bomb active and there is collision only then return true
bool Bomb::collideHandlerBomb(StaticObject& staticObject)
{
	bool result;
	if (staticObject.getType() == VROCK)
	{
		result = staticObject.isCollide(m_rectangle.getGlobalBounds());
		if ((result == true) && (isActive() == true))
			return true;
	}
	return false;
}			


void Bomb::setState(unsigned int state)
{
	m_state = state;
}

Bomb::~Bomb()
{
}
