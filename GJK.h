#pragma once
#include "stdafx.h"
#include "Object.h"

class Simplex
{
public:
	std::vector<sf::Vector2f> points;

	void Add(sf::Vector2f a)
	{
		points.push_back(a);
	}

	sf::Vector2f getLast()
	{
		return points[points.size()-1];
	}

	void Remove(int a)
	{
		points.erase(points.begin() + a);
	}

	void Insert(sf::Vector2f point, int a)
	{
		points.insert(points.begin() + a, point);
	}
};

class GJK
{
public:
	GJK();

	//void Check(std::vector<std::vector<Object*>>, std::vector<std::vector<Object*>>);
	bool Check(Object*, Object*);
	bool containsOrigin(sf::Vector2f&);
	//sf::Vector2f tripleProduct(sf::Vector2f, sf::Vector2f, sf::Vector2f);
	sf::Vector2f support(Object*, Object*, sf::Vector2f);
	sf::Vector2f GetFarthest(std::vector<sf::Vector2f>, sf::Vector2f);
	//sf::Vector2f Cross(sf::Vector2f, sf::Vector2f);
	//float Dot(sf::Vector2f, sf::Vector2f);
	//sf::Vector2f Normalise(sf::Vector2f);
	Simplex simplex;

private:
};