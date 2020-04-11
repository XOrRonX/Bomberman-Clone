/*
   Main.cpp 
   
takes care of two things :
1. Read the Board.txt file and create all the matrix data structures to hold the
data from the file
2. Get the user input and pass it on to the game
Main has one key function called playGame which is endless loop until the
game ends getting a key from the user and doing the next move.

*/
//=============================include=====================================


#define _CRT_SECURE_NO_WARNINGS

#include <cmath>
#include <stdio.h>
#include <iostream>
#include "macros.h"
#include "Screen.h"
#include <fstream>
#include <string>
#include "Bomberman.h"
#include <sstream>
#include "Keyboard.h"

using std::cin;
using std::istream;

//============================Prototypes================================

// take care of readin all the input file into set of screens 
// calls readMatrix
char **fileToMatrix(std::ifstream &inputFile, unsigned int &numOfLines,
					                         unsigned int &numOfSteps);

// read one matrix calls allocateMatrix
char **readMatrix(std::ifstream &inputFile, unsigned int numOfLines);

// set the memmory allocation of the matrix of chars
char **allocateMatrix(unsigned int numOfLines);

// read all the file into the game calls fileToMatrix
Bomberman readFileToGame(const char *fileName, unsigned int &numOfScreens,
			  char **arrayOfMatrixes[], unsigned int arrayOfMatrixSize[]);

// endless loop till game end of getting a key and sending it to 
// the class Bomberman myGame
void playGame(Bomberman myGame);

// read empty lines in the input file
bool notEmptyLine(char *numString);

// get the next special key from the user
int getKey();

// free all allocated memeory from reading file  
void freeMatrixes(unsigned int numOfScreens, char **arrayOfMatrixes[],
unsigned int arrayOfMatrixSize[]);


//==========================================main=============================

int main()
{
	char fileName[10] = "Board.txt";
	char **arrayOfMatrixes[MAX_SCREENS];
	unsigned int arrayOfMatrixSize[MAX_SCREENS];
	unsigned int numOfScreens = 0;
	int i;
	Bomberman myGame = readFileToGame(fileName, numOfScreens, 
								arrayOfMatrixes, arrayOfMatrixSize);
	playGame(myGame);

	freeMatrixes(numOfScreens,
				arrayOfMatrixes, arrayOfMatrixSize);


	// so the screen does not close 
	cin >> i;
}


void freeMatrixes(unsigned int numOfScreens, char **arrayOfMatrixes[],
				  unsigned int arrayOfMatrixSize[])
{
	char **tempMatrix;
	for (unsigned int i = 0; i < numOfScreens; i++)
	{
		tempMatrix = arrayOfMatrixes[i];
		for (unsigned int j = 0; j < arrayOfMatrixSize[i]; j++)
			free(tempMatrix[j]);
		free(tempMatrix);
	}
}



// get the key from the user
int getKey()
{
	while (true)
	{
		int key = Keyboard::getch();
		switch (key)
		{
		case ' ':
			return SKIP;
		case 'h':
			return HARDER;
		case 'e':
			return EASIER;
		case 'b':
			return BOMB;
		case 0:
		case SPECIAL_KEY:
			key = Keyboard::getch();
			switch (key)
			{
			case KB_UP:
				return UP;
			case KB_LEFT:
				return LEFT;
			case KB_RIGHT:
				return RIGHT;
			case KB_DOWN:
				return DOWN;
			}
		}
	}
}


// endless loop of playing game
void playGame(Bomberman myGame)
{
	int key;
	bool gameNotDone = true;
	unsigned int state;

	while (gameNotDone)
	{
		myGame.printScreen();
		key = getKey();
		state = myGame.nextMove(key);
		if (state == GAME_WON)
		{
			myGame.printScreen();
			printf("\n********WELL DONE GAME WON*********\n");
			gameNotDone = false;
		}
		if (state == GAME_OVER)
		{
			myGame.printScreen();
			printf("\n********ROBOT KILLED THREE TIMES GAME OVER********\n");
			gameNotDone = false;
		}
	}


}


// read the input file into a game using lost of functions
// returns the game of class Bomberman
Bomberman readFileToGame(const char *fileName, unsigned int &numOfScreens,
	              char **arrayOfMatrixes[], unsigned int arrayOfMatrixSize[])
{
	unsigned int numOfLines, numOfSteps;
	char **matrix;
	bool moreScreens = true;
	Bomberman myGame;
	std::ifstream inFile;

	inFile.open(fileName);
	if (!inFile.is_open())
	{
		std::cerr << "fopen failed\n";
		exit(EXIT_FAILURE);
	}

	// read all screens up to MAX_SCREENS screens
	while ((moreScreens == true) && (numOfScreens < MAX_SCREENS))
	{
		// get the next screen 
		matrix = fileToMatrix(inFile, numOfLines, numOfSteps);
		arrayOfMatrixes[numOfScreens] = matrix;
		arrayOfMatrixSize[numOfScreens] = numOfLines;
		if (matrix == NULL)
		{
			moreScreens = false;
			inFile.close();
			continue;
		}
		// add the new screen to the game
		myGame.addScreen(matrix, numOfLines, numOfSteps);
		numOfScreens++;
	}
	return myGame;
}

// read one matrix from file including size of matrix and number of steps
char **fileToMatrix(std::ifstream &inputFile, unsigned int &numOfLines,
	                unsigned int &numOfSteps)
{
	char numString[MAX_LINE_SIZE];
	char **matrix;
	std::stringstream ss;
	std::string temp;
	
	while (true)
	{
		inputFile.getline(numString, MAX_LINE_SIZE);
		if (inputFile.eof())
			return NULL;
		if (notEmptyLine(numString))
			break;
	}
	ss << numString;
	ss >> temp;
	std::stringstream(temp) >> numOfLines;
	ss >> temp;
	std::stringstream(temp) >> numOfSteps;
	matrix = readMatrix(inputFile, numOfLines);
	return matrix;
}


// return true of the line is not empty and false if it is
bool notEmptyLine(char *numString)
{
	unsigned int i = 0;
	while ((true) && (i < MAX_LINE_SIZE))
	{
		if (numString[i] != ' ' && numString[i] != '\0')
			return true;
		if (numString[i] == '\0')
			return false;
		i++;
	}
	return false;
}


// takes care of reading one matrix from a file
char **readMatrix(std::ifstream &inputFile, unsigned int numOfLines)
{
	char **matrix = allocateMatrix(numOfLines);
	char oneLine[MAX_LINE_SIZE];
	for (unsigned int i = 0; i < numOfLines; i++)
	{
		inputFile.getline(oneLine,MAX_LINE_SIZE);
		for (unsigned int j = 0; j < numOfLines; j++)
			matrix[i][j] = oneLine[j];
	}
	return matrix;
}

// do the memory allocation for a matrix
char **allocateMatrix(unsigned int numOfLines)
{
	char **matrix = NULL;
	unsigned int i;
	matrix = new (std::nothrow) char*[numOfLines];
	if (matrix == NULL)
	{
		std::cerr << "New failed\n";
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < numOfLines; i++)
	{
		matrix[i] = new (std::nothrow) char[numOfLines];
		if (matrix[i] == NULL)
		{
			std::cerr << "New failed\n";
			exit(EXIT_FAILURE);
		}
	}
	return matrix;
}



