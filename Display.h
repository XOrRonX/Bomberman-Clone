
/*

Class Display
This class is managing a display
it is not aware of the game only of itself
It has the following data strauctures:
unsigned int m_displaySize - size of the display number of lines and columns
char **m_display - amtrix of chars include all the shape of a screen

*/

//=============================include=======================================

#pragma once

#include "Vertex.h"


//===========================Class Display==================================

class Display
{
public:
	Display();
	~Display();

	// constructor get size of screen and it get 
	// an alocated intialized matrix with a full screen
	// at the right size.
	Display(char **screen , unsigned int size);

	// input is i and j of a location 
	// output is the char in that location in the matrix
	char getChar(Vertex location) const;

	// input is i and j of a location and the char to set in that location
	// no output and the function update the location with the onChar on 
	// on the matrix
	void setChar(const char oneChar, Vertex location);

	// prints the matrix to the standard output
	void printDisplay() const;

	// input is a char to search and count in the matrix
	// the putput is how many times the char is in the matrix
	unsigned int countChar(char c);

	void resetDisplayToOriginal();


private:
	// size of the screen
	unsigned int m_displaySize;

	// the matrix of chars that is the screen
	char **m_display;
	char **m_originalDisplay;
};

