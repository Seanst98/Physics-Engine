#pragma once
#include "stdafx.h"
#include "Object.h"
#include "GJK.h"

class Edge
{
public:
	sf::Vector2f A;
	sf::Vector2f B;

	float distance;
	float index;
	sf::Vector2f normal;
	sf::Vector2f max;   //So far purely for clipping
};


class EPA : public GJK
{
public:
	EPA();

	void Update(Object*, Object*, Simplex*);
	Edge ClosestEdge(Simplex);
	void calcWinding(Simplex*);

	std::string winding;
	sf::Vector2f normal;
	float depth;

};
