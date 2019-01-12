#pragma once
#include "stdafx.h"
#include "AABB.h"

class Object
{
public:

	Object(std::string, std::string);

	void Update();
	void CreateConvexHull();
	std::vector<sf::Vector2f> GetPoints();
	sf::Vector2f GetLocalCentre();
	sf::Vector2f GetCentre();
	sf::Vector2f GetWidthHeight();
	void CalculateAABB();

	std::vector<sf::Vector2f> Hull;

	sf::Transform matrix;
	sf::Vector2f velocity;
	float Rvelocity;
	float mass;
	float restitution;
	float rotation;
	std::string kind;
	float width;
	float height;
	AABB* aabb;


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