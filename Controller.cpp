
#define _CRT_SECURE_NO_WARNINGS

#include "Controller.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>
#include "macros.h"
#include "Guard.h"
#include "Robot.h"
#include "Wall.h"
#include "Rock.h"
#include "Door.h"
#include "Present.h"
#include <time.h>
#include <Windows.h>
#include "Bomb.h"
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include "Ghost.h"
#include "Ghostbomb.h"


// takes care of all event we care only about a few
void Controller::eventHandler()
{
	sf::Event event{};
	bool result = false;

	//poll means not block on event 
	//becasue all the images need to move
	result = m_window->pollEvent(event);
	// in case no event still need to take care of collision 
	// on the screen
	if (result == false)
	{
		collideHandler();
		return;
	}

	switch (event.type)
	{
	case sf::Event::Closed:
		m_window->close();
		m_state = EXIT_GAME;
		return;
	case sf::Event::KeyPressed:
		keyPressedHandler(event);
		break;
	default:
		break;
	}
	collideHandler();
}

// The constructire that build all the screen
Controller::Controller(char *fileName,unsigned int stage) : 
							m_textures(19),   
							m_board(fileName) // reads the file into matrix
											 // and reads the time/bombs/size
{
		m_points = 0;
		m_life = MAX_LIFE;
		m_stage = stage; // which screen index is this 
		m_numOfBombs = m_board.boardInfo(BOMBS); // get the number of bombs
		m_time = m_board.getTime(); // get the time

	sf::Vector2f pos;
	
	//-------------sound section------------------

	if (!soundBuffer.loadFromFile("BOM_ST5.wav"))
		return;
	sound.setBuffer(soundBuffer);

	if (!soundBufferDoor.loadFromFile("open_door_3.wav"))
		return;
	soundDoor.setBuffer(soundBufferDoor);

	if (!soundBufferPresent.loadFromFile("coin_1.wav"))
		return;
	soundPresent.setBuffer(soundBufferPresent);

	if (!soundBufferBye.loadFromFile("bye.wav"))
		return;
	soundBye.setBuffer(soundBufferBye);
	

	
	//-------------image section------------------

	m_font.loadFromFile("Gabriola.TTF");
	if ( !m_textures[VROBOT].loadFromFile("robot.png")
		|| !m_textures[VGUARD].loadFromFile("guard.png")
		|| !m_textures[VWALL].loadFromFile("wall.png")
		|| !m_textures[VROCK].loadFromFile("Rock.png")
		|| !m_textures[VDOOR].loadFromFile("door.png")
		|| !m_textures[VPRESENT].loadFromFile("present.png")
		|| !m_textures[VBOMB].loadFromFile("bomb.png")
		|| !m_textures[VEXPLODED].loadFromFile("exploded.gif")
		|| !m_textures[V1].loadFromFile("1.png")
		|| !m_textures[V2].loadFromFile("2.png")
		|| !m_textures[V3].loadFromFile("3.png")
		|| !m_textures[VGHOST].loadFromFile("ghost.png")
		|| !m_textures[VGHOSTBOMB].loadFromFile("ghostbomb.png")
		|| !m_textures[VLIFE].loadFromFile("heart.png")
		)

	{
		m_window->close();
		return;
	}


	updateScreenBoundry(); //set he size of the screen will be used to check
						   // no image is getting out of the screen

	// this section go over the matrix that was read from the file
	// and call the relevant constructor of the rlevant image
	for (int i = 0; i < m_board.boardInfo(LINES); i++)
	{
		for (int j = 0; j < m_board.boardInfo(COLUMNS); j++)
		{
			// calcualte from the location in the matrix
			// the location on the screen
			pos = { (float) j * RECT_SIZE + SCREEN_MIN_X , 
					(float) i * RECT_SIZE + SCREEN_MIN_Y };
			switch (m_board.getChar(i, j))
			{
			case ROBOT:
				m_robotIndex = (unsigned int) m_gameObjects.size();
				m_gameObjects.push_back(std::make_unique<Robot,
										const sf::Vector2f&, 
										const sf::Vector2f&, 
										std::vector<sf::Texture>& >
										({ RECT_SIZE, RECT_SIZE }, pos, m_textures));
				break;
			case GUARD:
				m_gameObjects.push_back(std::make_unique<Guard, 
										const sf::Vector2f&, 
										const sf::Vector2f&, 
										std::vector<sf::Texture>& >
									({ RECT_SIZE, RECT_SIZE }, pos, m_textures));
				m_numOfGuards++;
				break;
			case GHOST: // a guard that can go through walls and throw bombs
						// on the robot
				m_gameObjects.push_back(std::make_unique<Ghost,
										const sf::Vector2f&,
										const sf::Vector2f&,
										std::vector<sf::Texture>& >
									({ RECT_SIZE, RECT_SIZE }, pos, m_textures));
			case WALL:
				m_gameStaticObjects.push_back(std::make_unique<Wall,
											  const sf::Vector2f&,
											  const sf::Vector2f&,
											  std::vector<sf::Texture>&,
											  const unsigned int&>
											 ({ RECT_SIZE, RECT_SIZE }, pos,
											  m_textures,VWALL));
				break;
			case ROCK:
				m_gameStaticObjects.push_back(std::make_unique<Rock,
											const sf::Vector2f&,
											const sf::Vector2f&,
											std::vector<sf::Texture>&,
											const unsigned int>
											({ RECT_SIZE, RECT_SIZE }, pos,
											m_textures, VROCK));
				break;
			case EXIT_DOOR:
				m_gameStaticObjects.push_back(std::make_unique<Door,
											const sf::Vector2f&,
											const sf::Vector2f&,
											std::vector<sf::Texture>&,
											const unsigned int>
											({ RECT_SIZE, RECT_SIZE }, pos,
											m_textures, VDOOR));
				break;
			case PRESENT:
				
				m_gameStaticObjects.push_back(std::make_unique<Present,
											const sf::Vector2f&,
											const sf::Vector2f&,
											std::vector<sf::Texture>&,
											const unsigned int>
											({ 30, 30 }, pos,
											m_textures, VPRESENT));

				break;
			case PRESENT_ROCK: // present under a rock
				m_gameStaticObjects.push_back(std::make_unique<Present,
					const sf::Vector2f&,
					const sf::Vector2f&,
					std::vector<sf::Texture>&,
					const unsigned int>
					({ 30, 30 }, pos,
						m_textures, VPRESENT));
				m_gameStaticObjects.push_back(std::make_unique<Rock,
					const sf::Vector2f&,
					const sf::Vector2f&,
					std::vector<sf::Texture>&,
					const unsigned int>
					({ RECT_SIZE, RECT_SIZE }, pos,
						m_textures, VROCK));
				
				break;
			case LIFE: // a present that is giving life in the shape of a heart
				m_gameStaticObjects.push_back(std::make_unique<Present,
					const sf::Vector2f&,
					const sf::Vector2f&,
					std::vector<sf::Texture>&,
					const unsigned int>
					({ 25, 25 }, pos,
						m_textures, VLIFE));
			}
		}
	}	
}

// calcualte the screen boundries to check impages not getting our of the screen
void Controller::updateScreenBoundry()
{
	m_screenBoundryMin.x = SCREEN_MIN_X ;
	m_screenBoundryMin.y = SCREEN_MIN_Y ;
	m_screenBoundryMax.x = (m_board.boardInfo(COLUMNS)-1) * RECT_SIZE + SCREEN_MIN_X ;
	m_screenBoundryMax.y = (m_board.boardInfo(LINES)-1) * RECT_SIZE + SCREEN_MIN_Y ;
}

Controller::~Controller() = default;

// the main function that execute the game on one screen
void Controller::run()
{
	// doing the allocation here and not in the constructure to avoid
	// all the screen windows appearing for a second when the game start
	m_window = std::make_unique<sf::RenderWindow>
	(sf::VideoMode(DEFAULT_SCREEN_SIZE, DEFAULT_SCREEN_SIZE), "Bomberman");

	if (m_board.getTime()!= -1)
		m_clock.restart();
	
	m_window->setVisible(true);
	unsigned int x = (unsigned int)m_screenBoundryMax.x + 600;
	unsigned int y = (unsigned int) m_screenBoundryMax.y;

	// need to keep a screen size at least at default size 
	// else when low number of lines or columns the view is very bad
	y < DEFAULT_SCREEN_SIZE ? y = DEFAULT_SCREEN_SIZE : y = y ;
	x < DEFAULT_SCREEN_SIZE ? x = DEFAULT_SCREEN_SIZE : x = x;

	m_window->setSize({ x,y });
	while (m_window->isOpen())
	{
		if (m_board.getTime() != -1)
			hendelTime();
		if (m_state == GAME_OVER)
			break;
		m_window->clear();
		for (auto& shape : m_gameStaticObjects)
			shape->draw(*m_window);
		for (auto& shape : m_bombsList)
		{
			shape->draw(*m_window);
			shape->bombHandle();
		}
		for (auto& shape : m_gameObjects)
			if (shape->getIsAlive())
				shape->draw(*m_window);
		m_gameObjects[m_robotIndex]->draw(*m_window);
		Sleep(10); 
		moveObjects();  // move all objects on the screen
		eventHandler(); // look for event 
		if (m_state != NORMAL) // if something happened in the move like
							   // ROBOT found a door or life ended leave 
			break;		
		printInfo(" ");
		m_window->display();
	}
	handleStateChange();
}


// takes care of the information printed on the left side of the screen
void Controller::printInfo(char * add_string)
{
	sf::Font font;
	char string[150];
	
	sprintf(string, "Points: %d \nLife: %d \nStage: %d\nbombs: %d \ntime: %.1f\n%s",
		m_points, m_life, m_stage, m_numOfBombs, m_time, add_string);
	font.loadFromFile("Gabriola.TTF");
	std::string str(string);
	sf::Text txt(str, font, 10);
	txt.setFillColor(sf::Color::Yellow);
	txt.setOutlineThickness(20);
	txt.setOutlineColor(sf::Color::Black);
	txt.setStyle(sf::Text::Bold);
	txt.setCharacterSize(30);
	txt.setPosition((float)m_screenBoundryMax.x + 50, (float)100);
	m_window->draw(txt);
}


void Controller::moveObjects()
{
	sf::Vector2f rbotLocation;
	rbotLocation = m_gameObjects[m_robotIndex]->getPosition();
	for (auto& shape : m_gameObjects)
	{
		shape->move(m_robotMove, m_screenBoundryMin, m_screenBoundryMax, rbotLocation);
		if ((m_state = shape->getState()) != NORMAL)
			return;
	}
}


void Controller::handleStateChange()
{
	if (m_state == ROBOT_FOUND_DOOR)
	{
		soundDoor.play();
		m_points += BONUS_EXIT_DOOR * m_numOfGuards;
	}
	if (m_state == GAME_OVER)
		m_window->close();
}

unsigned int Controller::getState() const
{
	return m_state;
}

void Controller::setPoints(unsigned int totalPoints)
{
m_points = totalPoints;
}

void Controller::setLife(unsigned int lifeLeft)
{
	m_life = lifeLeft;
}



void Controller::keyPressedHandler(const sf::Event& event)
{
	sf::Vector2f v{ 0,0 };
	switch (event.key.code)
	{
	case sf::Keyboard::Right:
		m_robotMove = { POS_PIXEL_MOVE,0 };
		break;
	case sf::Keyboard::Left:
		m_robotMove = { NEG_PIXEL_MOVE ,0 };
		break;
	case sf::Keyboard::Up:
		m_robotMove = { 0 , NEG_PIXEL_MOVE };
		break;
	case sf::Keyboard::Down:
		m_robotMove = { 0 , POS_PIXEL_MOVE };
		break;
	case sf::Keyboard::Space: //halt robot
		m_robotMove = { 0 , 0 };
		break;
	case sf::Keyboard::B: 
		if (m_numOfBombs > 0 || m_numOfBombs == -1)
		{
			sound.play();
			sf::Vector2f pos;
			pos = m_gameObjects[m_robotIndex]->getPosition();
			pos.x += 5;
			m_bombsList.push_back(std::make_unique<Bomb,
				const sf::Vector2f&,
				const sf::Vector2f&,
				std::vector<sf::Texture>&,
				const unsigned int>
				({ RECT_SIZE, RECT_SIZE },pos ,
					m_textures, VBOMB));
			if (m_numOfBombs != -1) // in case no infinite bombs count down
				m_numOfBombs--;
		}
		break;
	case sf::Keyboard::D:  // this is the key to leave a screen and restrat it
		resetRobot();
		if (m_state == GAME_OVER)
			return;
		restart();
		printInfo("You abandon\nthe game\nStarts over");
		m_window->display();
		soundBye.play();
		Sleep(3000);
		break;
	case sf::Keyboard::H: // control guard speed pressing once change speed
						  // to faster pressing again back to slower
		for (auto& shape : m_gameObjects)
			if (shape->getIsAlive())
				shape->changeGuardSpeed();
	default:
		break;
	}
}

// The big functions that takes of all collisions in the game
void Controller::collideHandler()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
	{

		//-------------------guard killed robot--------------------------

		if ( VGHOST != m_gameObjects[i]->getType() && m_gameObjects[m_robotIndex]->collideHandler(*m_gameObjects[i]) &&
			m_gameObjects[i]->getIsAlive() == true && i != m_robotIndex)
		{
			resetRobot();
			if (m_state == GAME_OVER)
				return;
		}
	

		if (VGHOST == m_gameObjects[i]->getType() && m_gameObjects[m_robotIndex]->collideHandler(*m_gameObjects[i]))
		{
			
			if (rand() % 34 == 0)
			{
				m_bombsList.push_back(std::make_unique<Ghostbomb,
					const sf::Vector2f&,
					const sf::Vector2f&,
					std::vector<sf::Texture>&,
					const unsigned int>
					({ RECT_SIZE, RECT_SIZE }, m_gameObjects[m_robotIndex]->getPosition(),
						m_textures, VGHOSTBOMB));
			}
			
		}
			

		//-----------------bomb killed gurad/robot/rock/presentrock ----------------------

		for (int l = 0; l < m_bombsList.size(); l++)
		{
			if (i != m_robotIndex && VGHOST != m_gameObjects[i]->getType() && m_bombsList[l]->getType() == VBOMB)
			{
				if (m_gameObjects[i]->collideHandler(*m_bombsList[l]) &&
					m_bombsList[l]->getState() == DURING_EXPLODED && 
					m_gameObjects[i]->getIsAlive())
				{
					m_gameObjects[i]->disable();
					m_points += (BONUS_GUARD_KILLED * m_numOfGuards);
				}
			}

			if (m_gameObjects[m_robotIndex]->collideHandler(*m_bombsList[l]) &&
				m_bombsList[l]->getState() == DURING_EXPLODED)
			{
				resetRobot();
				if (m_state == GAME_OVER)
					return;
			}
				

			for ( int k=0 ;  k < m_gameStaticObjects.size() ; k++)
				if (m_gameStaticObjects[k]->getType() == VROCK &&
					m_bombsList[l]->collideHandlerBomb(*m_gameStaticObjects[k])&&
					m_bombsList[l]->getState() == DURING_EXPLODED &&
					m_bombsList[l]->getType() == VBOMB )
						m_gameStaticObjects[k]->disable();
		}

		//-----------------check collision with static objects----------------------

		for (int j = 0 ; j < m_gameStaticObjects.size(); j++)
		{
			if (m_gameObjects[i]->collideHandlerStatic(*m_gameStaticObjects[j]))
			{
				if (i != m_robotIndex)
					m_gameObjects[i]->m_guardCollide = true;
				m_gameObjects[i]->moveRevert();
			}
			m_state = m_gameObjects[i]->getState();
			if (m_state == ROBOT_FOUND_DOOR)
				return;
			if (m_state == ROBOT_FOUND_PRESENT || m_state == ROBOT_FOUND_LIFE)
			{
				soundPresent.play();
				m_gameStaticObjects[j]->disable();
				m_gameStaticObjects[j]->changeActive();
				if (m_numOfBombs != -1 && m_state == ROBOT_FOUND_PRESENT)
					m_numOfBombs++;
				if (m_state == ROBOT_FOUND_LIFE)
					m_life++;
				m_state = NORMAL;
				m_gameObjects[i]->changeState();
				return;
			}

		}
	}

}


// called after robot is killed 
void Controller::resetRobot()
{
	m_life--;
	if (m_life == 0)
	{
		m_state = GAME_OVER;
		printInfo("GAME LOST \n  ;-(");
		m_window->display();
		Sleep(3000);
		return;
	}

	// 
	m_robotMove = { 0, 0 };
	// get the robot to its original location 
	// increase size to check collissions with bombs in original location.
	// in case of collision remove the bombs
	m_gameObjects[m_robotIndex]->setSize({ 150,150 }); 
	m_gameObjects[m_robotIndex]->setToDefault();
	m_gameObjects[m_robotIndex]->setPosition({-35 ,-35});
	for (int l = 0; l < m_bombsList.size(); l++)
	{
		if (m_gameObjects[m_robotIndex]->collideHandler(*m_bombsList[l]))
		{
			m_bombsList[l]->disable();
			m_bombsList[l]->setState(AFTER_EXPLODED);
		}
	}

	// get back to normal size and return all the guards to their original location 
	m_gameObjects[m_robotIndex]->setSize({ RECT_SIZE,RECT_SIZE });
	m_gameObjects[m_robotIndex]->setToDefault();
	for (int k = 0; k < m_gameObjects.size(); k++)
	{
		if ((k != m_robotIndex) && (m_gameObjects[k]->getIsAlive())) 
			m_gameObjects[k]->setToDefault();
		
	}
}

void Controller::closeWindow()
{
	m_window->close();
}

void Controller::display() const 
{
	m_window->display();
}

void Controller::hendelTime()
{
	if (m_time == -1)
		return;
	m_t = m_clock.getElapsedTime();
	m_time = m_t.asSeconds();
	m_time = m_time * -1 + m_board.getTime();
	if (m_time <= 0)
	{
		resetRobot();
		if (m_state == GAME_OVER)
			return;
		restart();
		printInfo("Time Ended \nRestarting\n");
		m_window->display();
		Sleep(3000);
		m_clock.restart();
	}

}

// this is called after time ended or after user decided 
// to get out of a screen and restart it.
// it gets all objects to their orginal place and status
void Controller::restart()
{
	for (auto& shape : m_gameObjects)
		shape->setToDefault();
	for (auto& shape : m_gameStaticObjects)
		shape->backToDefault();
	m_time = m_board.getTime();
	m_numOfBombs = m_board.boardInfo(BOMBS);
	m_robotMove = { 0 , 0 };
}


unsigned int Controller::getPoints() const
{
	return m_points;
}
unsigned int Controller::getLife() const
{
	return m_life;
}


