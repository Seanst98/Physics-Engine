#pragma once
#include "stdafx.h"

class Object
{
public:

	Object(std::string);

	void Update();

	sf::Transform matrix;

	sf::VertexArray *ptr;

	unsigned int ID;

};