#include "Board.h"
#include "macros.h"
#include <string>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <sstream>
#include <iostream>

Board::Board()
{
}


Board::~Board()
{
}


//=============================ScreenFile==============================

//read file to matrix of chars and read columns and lines size
//if file does not exist then create a file with default data and size
Board::Board(char *fileName)
{

	//strcpy(m_fileName, fileName);
	m_file.open(fileName);
	if (!m_file.is_open()) // if the file does not exist
	{
		std::cerr << "Open File Failed \n";
		exit(EXIT_FAILURE);
	}
	else // the file exist, read it to char matrix and columns/lines
	{
		// get the next screen 
		fileToMatrix();
		m_file.close();
	}
}

//=============================numString======================================

// read one matrix from file including size of lines and columns
void Board::fileToMatrix()
{
	char numString[MAX_LINE_SIZE];
	std::stringstream ss;
	std::string temp;
	//int lines, columns;

	while (true) // read all empty lines till first line
	{
		m_file.getline(numString, MAX_LINE_SIZE);
		if (m_file.eof())
			return;
		if (notEmptyLine(numString))
			break;
	}
	ss << numString;
	for (int i = LINES; i < BOMBS + 1; i++)
	{
		ss >> temp;
		if (i!=TIME)
			std::stringstream(temp) >> m_boardInfo[i];
		else
			std::stringstream(temp) >> m_time;
	}
	readMatrix();
}

//=============================notEmptyLine===================================

// return true of the line is not empty and false if it is
bool Board::notEmptyLine(char *numString)
{
	for (int i = 0; i < MAX_LINE_SIZE && numString[i] != '\0'; i++)
		if (numString[i] != ' ' && numString[i] != '\0')
			return true;
	return false;
}

//=============================readMatrix===================================

// takes care of reading one matrix from a file
void Board::readMatrix()
{
	char oneLine[MAX_LINE_SIZE];
	for (int i = 0; i < m_boardInfo[LINES] ; i++)
	{
		std::vector<char> row;

		m_file.getline(oneLine, MAX_LINE_SIZE);
		for (int j = 0; j < m_boardInfo[COLUMNS]; j++)
			row.push_back(oneLine[j]);
		m_boardMatrix.push_back(row);
	}
}

char Board::getChar(unsigned int i, unsigned int j) const
{
	return m_boardMatrix[i][j];
}

int Board::boardInfo(int type) const
{
	return m_boardInfo[type];
}

float Board::getTime() const
{
	return m_time;
}




