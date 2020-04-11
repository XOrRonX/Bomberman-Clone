
/*
Class Controller
this class is the main class of the project
it manages a game and it holds in it all the objects of one screen
it also manages all the moves in the game 

*/


#pragma once
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "BaseObject.h"
#include "Board.h"
#include "StaticObject.h"
#include "macros.h"
#include "Bomb.h"
#include "Ghostbomb.h"


class Controller
{
public:
	
	Controller(char *fileName,unsigned int stage);
	~Controller();

	// returns the state of the controller 
	unsigned int getState() const;

	// set the points from previos controller
	void setPoints(unsigned int m_totalPoints);

	// set the life from previous controller 
	void setLife(unsigned int m_lifeLeft);

	// the main function that execute the flow of the screen
	void run();

	// returns how many points the screen won
	unsigned int getPoints() const ;

	// returns how many life are left to the robot
	unsigned int getLife() const ;

	void closeWindow();
	void display() const;

	// print the info on the right side of the screen
	void printInfo(char * string);

private:

	// handle the different key press
	void keyPressedHandler(const sf::Event& event);

	// main functions managing all the collisions 
	void collideHandler();

	// poll for event if availbale check and act and if not continue
	void eventHandler();

	// hadles cases of state change like robot found a door 
	// or all the life of the robot are gone
	void handleStateChange();

	// calcaulate the boundries of the screen so no object
	// gets out of the screen 
	void updateScreenBoundry();

	// moves the object 
	void moveObjects();

	// takes care of the time count down of the screen 
	void hendelTime();

	// restart the whole screen to its initial state not including 
	// life or points which
	void restart();

	// return the robot to its orginila location and remove
	// all the bombs around that location 
	void resetRobot();

	std::unique_ptr<sf::RenderWindow> m_window;
	std::vector<sf::Texture> m_textures;
	std::vector<std::unique_ptr<BaseObject>> m_gameObjects; // guards/robot/ghost
	std::vector<std::unique_ptr<StaticObject>> m_gameStaticObjects; 
	std::vector<std::unique_ptr<Bomb>> m_bombsList; // all the bombs
	sf::Vector2f m_robotMove = { 0,0 };  // track the next move of the robot
	Board m_board; // holds the matrix of the board read from the file
	sf::Vector2f m_screenBoundryMax;
	sf::Vector2f m_screenBoundryMin;
	unsigned int m_state = NORMAL;
	sf::Font m_font;
	unsigned int m_points;
	unsigned int m_life ;
	unsigned int m_stage; //which screen is it
	int m_numOfBombs ;  // hold how many bombs were put in the file
	unsigned int m_numOfGuards = 0; // for bonus count all guards 
	float m_time; // time of the screen
	sf::Time m_t;
	sf::Clock m_clock;
	unsigned int m_robotIndex; // the index in the vector where the robot
	std::vector<std::unique_ptr<Ghostbomb>> m_ghostBmobList;
	sf::SoundBuffer soundBuffer;
	sf::Sound sound;
	sf::SoundBuffer soundBufferDoor;
	sf::Sound soundDoor;
	sf::SoundBuffer soundBufferPresent;
	sf::Sound soundPresent;
	sf::SoundBuffer soundBufferBye;
	sf::Sound soundBye;

};

