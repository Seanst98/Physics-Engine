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
	Edge bestEdge(Object*, sf::Vector2f);

};
