#pragma once
#include "stdafx.h"

class ResourceManager
{
public:

	void DefineTriangle();
	void DefineQuad();
	void DefinePrzemekShape();
	void DefinePentagon();

	std::vector<sf::Vector2f> GetPoints(std::string);
	sf::VertexArray* Get(std::string);

private:

	std::map<std::string, sf::VertexArray> resources;

	sf::VertexArray triangle;
	sf::VertexArray quad;
	sf::VertexArray pentagon;
	sf::VertexArray przemek;

};