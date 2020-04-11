#pragma once

// Class StaticObject
// takes care of all the static objects in the game
// bomb, door, present, life, rock, wall

#include <SFML/Graphics.hpp>

class StaticObject
{
public:
	StaticObject(const sf::Vector2f& size, const sf::Vector2f& pos,
		std::vector<sf::Texture>& textures, const unsigned int index);
	~StaticObject();
	StaticObject(std::vector<sf::Texture>& textures);

	// returns true if the object is active 
	bool isActive() const;

	// returns the object to its original state and position 
	void backToDefault();

	// disable the object so it is not effecting the game 
	void disable();

	// draw the object on the renderWindow
	void draw(sf::RenderWindow& renderWindow);

	// returns true if this and rect have a collision 
	bool isCollide(const sf::FloatRect& rect) const;

	// Switch state if active make not and the other way around
	void changeActive();

	// change the picture for example for the bomb states
	void updatePicture(unsigned int index);

	// update the size of the rectangle 
	void changeSize(const sf::Vector2f& size);

	// return the position of an object
	sf::Vector2f getPos() const ;

	// returns the object type bomb, door, wall and so on
	unsigned int getType() const ;

protected: // accessed by children
	sf::RectangleShape m_rectangle;
	unsigned int m_objectType;
	
private:
	bool m_active;
	int m_index;
	std::vector<sf::Texture>& m_textures;
	sf::Vector2f m_originalPosition;
	unsigned int m_type;
};

