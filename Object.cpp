#pragma once
#include "stdafx.h"
#include "Object.h"
#include "ResourceManager.h"
#include "Game.h"
#include "GJK.h"
#include "Math.h"

Object::Object(std::string name, std::string kin)
{
	ptr = Game::resManager.Get(name);
	type = name;
	kind = kin;


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

float Object::GetInvMass()
{
	if (kind != "wall")
	{
		return 1 / mass;
	}
	else
	{
		return 0;
	}
}

//COME BACK TO THIS AND FIX/FIND BETTER WAY
//Get Farthest method works but unsure if more efficient
void Object::CalculateAABB()
{
	sf::Vector2f xmax = GetFarthest(this->GetPoints(), (sf::Vector2f(1, 0)));
	sf::Vector2f xmin = GetFarthest(this->GetPoints(), (sf::Vector2f(-1, 0)));
	sf::Vector2f ymax = GetFarthest(this->GetPoints(), (sf::Vector2f(0, 1)));
	sf::Vector2f ymin = GetFarthest(this->GetPoints(), (sf::Vector2f(0, -1)));

	/*std::vector<sf::Vector2f> points = GetPoints();
	std::vector<float> pointsX;
	std::vector<float> pointsY;

	for (int i = 0; i < points.size(); i++) {
		pointsX.push_back(points[i].x);
		pointsY.push_back(points[i].y);
	}

	auto xmaxit = std::max_element(pointsX.begin(), pointsX.end());
	float xmax = *xmaxit;

	auto xminit = std::min_element(pointsX.begin(), pointsX.end());
	float xmin = *xminit;

	auto ymaxit = std::max_element(pointsY.begin(), pointsY.end());
	float ymax = *ymaxit;

	auto yminit = std::min_element(pointsY.begin(), pointsY.end());
	float ymin = *yminit;*/

	AABB *aabb = new AABB(xmin.x-10, ymin.y-10, xmax.x+10, ymax.y+10);
	aabb->object = this;

	this->aabb = aabb;
}

sf::Vector2f Object::GetLocalCentre()
{
	sf::Vector2f point;

	std::vector<sf::Vector2f> points;
	points = Game::resManager.GetPoints(type);

	int sumx = 0;
	int sumy = 0;

	for (int i = 0; i < points.size(); i++) {

		sumx = points[i].x + sumx;
		sumy = points[i].y + sumy;
	}

	sumx = sumx / points.size();
	sumy = sumy / points.size();

	sf::Vector2f ret;
	ret.x = sumx;
	ret.y = sumy;

	return ret;
}

sf::Vector2f Object::GetCentre()
{
	sf::Vector2f point;

	std::vector<sf::Vector2f> points;
	points = GetPoints();

	int sumx = 0;
	int sumy = 0;

	for (int i = 0; i < points.size(); i++) {
		sumx = points[i].x + sumx;
		sumy = points[i].y + sumy;
	}

	sumx = sumx / points.size();
	sumy = sumy / points.size();

	sf::Vector2f ret;
	ret.x = sumx;
	ret.y = sumy;

	return ret;
}

sf::Vector2f Object::GetWidthHeight() {

	sf::Vector2f ret;

	float rot = std::fmod(rotation, 360);

	rot = 360 - rot;

	matrix.rotate(rot, GetLocalCentre());

	ret = GetPoints()[2] - GetPoints()[0];

	matrix.rotate(rotation, GetLocalCentre());

	return ret;
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
	if (kind != "wall") {
		float rot = std::fmod(rotation, 360);

		rot = 360 - rot;

		matrix.rotate(rot, GetLocalCentre());

		matrix.translate(velocity.x*ET, velocity.y*ET);

		velocity.y += ET * 100;

		matrix.rotate(rotation, GetLocalCentre());

		//matrix.rotate(25 * ET, GetCentre());
		//rotation += 25 * ET;

		//float rot = Math::Magnitude(Rvelocity);

		matrix.rotate(Rvelocity*ET, GetLocalCentre());

		sf::CircleShape shape(5);

		shape.setFillColor(sf::Color::Green);
		shape.setPosition(GetCentre());

		Game::mainWindow.draw(shape);

		rotation += Rvelocity * ET;

	}
	else {
		velocity.x = 0;
		velocity.y = 0;
		Rvelocity = 0;
	}

	CalculateAABB();

}