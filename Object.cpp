#pragma once
#include "stdafx.h"
#include "Object.h"
#include "ResourceManager.h"
#include "Game.h"
#include "GJK.h"

Object::Object(std::string name)
{
	ptr = Game::resManager.Get(name);
	type = name;

	//CreateConvexHull();
}

std::vector<sf::Vector2f> Object::GetPoints()  //Return transformed points
{
	std::vector<sf::Vector2f> points;

	points = Game::resManager.GetPoints(type);

	for (int i = 0; i < points.size(); i++)
	{
		points[i] = matrix.transformPoint(points[i]);
	}

	return points;
}

/*void Object::CreateConvexHull()
{
	auto points = GetPoints();

	float maxX = points[0].x;
	float maxI = 0;  //Max index

	float minX = points[0].x;
	float minI = 0;  //Min index

	for (int i = 1; i < points.size()-1; i++)
	{
		float tempmaxX = points[i].x;
		float tempminX = points[i].x;

		if (tempmaxX > maxX)
		{
			maxX = tempmaxX;
			maxI = i;
		}
		if (tempminX < minX)
		{
			minX = tempminX;
			minI = i;
		}
	}


	Hull.push_back(points[minI]);
	Hull.push_back(points[maxI]);


	sf::Vector2f B = points[maxI];
	sf::Vector2f A = points[minI];
	sf::Vector2f AB = B - A;

	for (int j = 0; j < points.size() - 1; j++)
	{
		if 
	}

	//FindHull(S1, A, B);
	//FindHull(S2, B, A);  //BA so that perp is in opposite direction

}

std::vector<sf::Vector2f> Object::FindHull(std::vector<sf::Vector2f> S, sf::Vector2f A, sf::Vector2f B)
{
	if (S.size() == 0)
	{
		return;
	}

	sf::Vector2f perp;
	sf::Vector2f AB = B - A;

	perp.x = AB.x;
	perp.y = (-AB.x * perp.x) / AB.y;

	sf::Vector2f point = GetFarthest(S, perp);

	Hull.insert(Hull.begin() + 1, point);


}*/

/*std::vector<sf::Vector2f> Object::Recursive(sf::Vector2f A, sf::Vector2f B, sf::Vector2f C, std::vector<sf::Vector2f> points, std::vector<sf::Vector2f> Hull)
{
	//C IS THE FAR POINT

	sf::Vector2f AC = C - A;
	sf::Vector2f perp;
	perp.x = AC.x;
	perp.y = (-AC.x * perp.x) / AC.y;

	sf::Vector2f point = GetFarthest(points, perp);

	Hull.push_back(A);
	Hull.push_back(C);

	if (point == C || point == A) { return Hull; }
	return Recursive(A, B, point, points, Hull);

}*/

sf::Vector2f Object::GetFarthest(std::vector<sf::Vector2f> points, sf::Vector2f d)
{
	sf::Vector2f farthest;
	float farDistance = -9999999999999;

	for (int i = 0; i < points.size(); i++)
	{
		float temp = Dot(d, points[i]);

		if (temp > farDistance)
		{
			farDistance = temp;
			farthest = points[i];
		}
	}

	return farthest;
}

float Object::Dot(sf::Vector2f A, sf::Vector2f B)
{
	return (A.x * B.x) + (A.y * B.y);
}

void Object::Update()
{

}