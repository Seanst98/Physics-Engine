#pragma once
#include "stdafx.h"
#include "ResourceManager.h"

void ResourceManager::DefineTriangle()
{
	sf::Vertex a;
	sf::Vertex b;
	sf::Vertex c;

	a.position = sf::Vector2f(0, 0);
	b.position = sf::Vector2f(100, 0);
	c.position = sf::Vector2f(100, 100);

	a.color = sf::Color::Blue;
	b.color = sf::Color::Blue;
	c.color = sf::Color::Blue;

	triangle.setPrimitiveType(sf::Triangles);

	triangle.append(a);
	triangle.append(b);
	triangle.append(c);

	resources.insert(std::pair<std::string, sf::VertexArray>("triangle", triangle));
}

sf::VertexArray* ResourceManager::Get(std::string name)
{
	std::map<std::string, sf::VertexArray>::iterator results = resources.find(name);
	if (results == resources.end())  //If the object does not exist then return a null pointer
		return nullptr;

	return &(results->second);

}