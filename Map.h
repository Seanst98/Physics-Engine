#pragma once
#include "stdafx.h"
#include "Object.h"
#include "NSquared.h"

class Map
{
public:
	Map();
	~Map();

	void Add(Object* gameObject);
	void Remove(unsigned int name);
	void RemoveAll();
	Object* Get(unsigned int ID);
	int Size();

	void DrawAll(sf::RenderWindow& renderWindow);
	void UpdateAll();
	void Collisions();

	std::vector<Object*> Objects;

	NSquared nsquared;

private:
};