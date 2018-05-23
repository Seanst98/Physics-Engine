#pragma once
#include "stdafx.h"
#include "Map.h"

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

