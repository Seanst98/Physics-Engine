#pragma once
#include "stdafx.h"

class ResourceManager
{
public:

	void DefineTriangle();
	sf::VertexArray* Get(std::string);

private:

	std::map<std::string, sf::VertexArray> resources;

	sf::VertexArray triangle;
};