#pragma once
#include "stdafx.h"

class Object
{
public:

	Object(std::string);

	void Update();
	void CreateConvexHull();
	std::vector<sf::Vector2f> GetPoints();
	sf::Vector2f GetCentre();

	std::vector<sf::Vector2f> Hull;

	sf::Transform matrix;
	sf::Vector2f velocity;
	float Rvelocity;
	float mass;
	float restitution;
	float rotation;

	sf::VertexArray *ptr;
	sf::VertexArray *Cptr;

	unsigned int ID;

	bool checked = false;

	std::string type;

	sf::Vector2f GetFarthest(std::vector<sf::Vector2f>, sf::Vector2f);
	float Dot(sf::Vector2f, sf::Vector2f);

	std::vector<sf::Vector2f> FindHull(std::vector<sf::Vector2f>, sf::Vector2f, sf::Vector2f);

	//std::vector<sf::Vector2f> Recursive(sf::Vector2f, sf::Vector2f, sf::Vector2f, std::vector<sf::Vector2f>, std::vector<sf::Vector2f>);


};