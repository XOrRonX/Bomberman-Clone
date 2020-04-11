#include "Vertex.h"
#include "macros.h"


int Vertex::verticalDifference(const Vertex& other) const
{
    return m_i - other.m_i;
}

int Vertex::horizontalDifference(const Vertex& other) const
{
    return m_j - other.m_j;
}

bool Vertex::isEqual(const Vertex & other) const
{
	return m_j == other.m_j && m_i == other.m_i;
}



void Vertex::copy(const Vertex& other)
{
	m_j = other.m_j;
	m_i = other.m_i;
}

void Vertex::moveVertex(unsigned int direction)
{
	switch (direction)
	{	
	case UP:
		m_i--;
		break;
	case DOWN:
		m_i++;
		break;
	case LEFT:
		m_j--;
		break;
	case RIGHT:
		m_j++;
		break;
	}
}