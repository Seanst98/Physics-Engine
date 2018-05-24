#pragma once
#include "stdafx.h"
#include "Object.h"
#include "GJK.h"
#include "EPA.h"

class Contact : public GJK
{
public:
	Contact();

	void getPoints(Object*, Object*, sf::Vector2f, float);
	Edge bestEdge(std::vector<sf::Vector2f>, sf::Vector2f);
	std::vector<sf::Vector2f> clipping(Edge, Edge, sf::Vector2f);
	std::vector<sf::Vector2f> clip(sf::Vector2f, sf::Vector2f, sf::Vector2f, float);

};
