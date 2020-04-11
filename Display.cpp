
/*

Class Display
This class is managing a display
it is not aware of the game only of itself
It has the following data strauctures:
unsigned int m_displaySize - size of the display number of lines and columns
char **m_display - amtrix of chars include all the shape of a screen

*/

//=============================include=======================================


#include "Display.h"
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include "macros.h"



Display::Display()
{
}


// frees the allocated matrix 
Display::~Display()
{
}


// the constructore does not allocate the matrix
// it gets an already allocation matrix
Display::Display(char **screen, unsigned int size)
{
	m_originalDisplay = screen;
	m_displaySize = size;
	m_display = NULL;

	m_display = new (std::nothrow) char*[size];
	if (m_originalDisplay == NULL)
	{
		std::cerr << "New failed\n";
		exit(EXIT_FAILURE);
	}
	for (unsigned int i = 0; i < size; i++)
	{
		m_display[i] = new (std::nothrow) char[size];
		if (m_display[i] == NULL)
		{
			std::cerr << "New failed\n";
			exit(EXIT_FAILURE);
		}
	}

	resetDisplayToOriginal();
}


// copy the original display to m_display
// this is needed for when the steps of the robot got to 0
void Display::resetDisplayToOriginal()
{
	for (unsigned int i = 0; i < m_displaySize; i++)
		for (unsigned int j = 0; j < m_displaySize; j++)
			m_display[i][j] = m_originalDisplay[i][j];
}

// returns the char in location
// if the locatoin is outside the screen return ERROR
char Display::getChar(Vertex location) const
{
	if (location.m_j >= m_displaySize || location.m_j < 0 ||
		location.m_i >= m_displaySize || location.m_i < 0)
		return ERROR;
	return m_display[location.m_i][location.m_j];
}


//set oneChar in location 
// if location is outside the screen do nothing
void Display::setChar(const char oneChar, Vertex location)
{
	if (location.m_j >= m_displaySize || location.m_j < 0 ||
		location.m_i >= m_displaySize || location.m_i < 0)
		return;
	m_display[location.m_i][location.m_j] = oneChar;
}


// print the screen after cleating the screen
void Display::printDisplay() const
{
	system("CLS");
	for (unsigned int i = 0; i < m_displaySize; i++)
	{
		for (unsigned int j = 0; j < m_displaySize; j++)
		{
			std::cout << m_display[i][j];
		}
		std::cout << '\n';
	}
}

// returns how many times char C is in the screen
unsigned int Display::countChar(char c)
{
	unsigned int counter = 0;
	for (unsigned int i = 0; i < m_displaySize; i++)
	{
		for (unsigned int j = 0; j < m_displaySize; j++)
		{
			if (m_display[i][j] == c)
				counter++;
		}
	}
	return counter;
}



