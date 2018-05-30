#pragma once
#include "stdafx.h"
#include "Map.h"
#include "EPA.h"
#include "Contact.h"
#include "Resolution.h"
#include "SpatialGrid.h"

Map::Map(){}

Map::~Map(){}

void Map::Add(Object* Object)
{
	Objects.push_back(Object);
}

void Map::Remove(unsigned int ID)
{
	auto itr = Objects.begin();

	while (itr != Objects.end())
	{
		if ((*itr)->ID == ID) 
		{
			Objects.erase(itr);
			break;
		}

		itr++;
	}
}

void Map::RemoveAll()
{
	Objects.clear();
}

int Map::Size()
{
	return Objects.size();
}

Object* Map::Get(unsigned int ID)
{
	for (int i = 0; i < Objects.size(); i++)
	{
		if (Objects[i]->ID == ID) { return Objects[i]; }
	}
}

void Map::DrawAll(sf::RenderWindow& mainWindow)
{
	auto itr = Objects.begin();

	for (int i = 0; i < Objects.size(); i++)
	{
		sf::VertexArray *a = (*itr)->ptr;

		mainWindow.draw((*a), (*itr)->matrix);

		itr++;
	}
}

void Map::UpdateAll()
{
	auto itr = Objects.begin();

	while (itr != Objects.end())
	{
		(*itr)->Update();
		itr++;
	}
}

void Map::Collisions()
{
	
	for (int i = 0; i < Objects.size(); i++) {
		SpatialGrid grid;
		grid.Update();

		GJK gjk;

		int j = 0;

		if (i == Objects.size() - 1) {
			j = 0;
		}
		else {
			j = i + 1;
		}

		if (gjk.Check(Objects[i], Objects[j])) {
			EPA epa;
			epa.Update(Objects[i], Objects[j], &gjk.simplex);

			Contact contacts;
			contacts.getPoints(Objects[i], Objects[j], epa.normal, epa.depth);

			Resolution resolution;
			resolution.Update(Objects[i], Objects[j], contacts.clippedPoints, epa.normal);
		}
	}
	/*auto itr = Objects.begin();

	while (itr != Objects.end()-1)
	{
		SpatialGrid grid;
		grid.Update();

		GJK gjk;

		if (gjk.Check((*itr), (*itr+1)))
		{
			EPA epa;
			epa.Update((*itr), (*itr+1), &gjk.simplex);

			Contact contacts;
			contacts.getPoints((*itr), (*itr+1), epa.normal, epa.depth);

			Resolution resolution;
			resolution.Update((*itr), (*itr+1), contacts.clippedPoints, epa.normal);
		}

		itr++;
	}*/
}

