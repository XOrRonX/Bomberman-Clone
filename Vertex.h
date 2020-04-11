#pragma once

struct Vertex
{

	unsigned int m_j;
	unsigned int m_i;

    int verticalDifference(const Vertex& other) const;
	int horizontalDifference(const Vertex& other) const;
	bool isEqual(const Vertex& other) const;
	void copy(const Vertex& other);
	void moveVertex(unsigned int direction);
	
};
