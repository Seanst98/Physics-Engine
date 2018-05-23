#include "stdafx.h"
#include "SpatialGrid.h"
#include "Map.h"
#include "Game.h"
#include "GJK.h"
#include "EPA.h"

SpatialGrid::SpatialGrid()
{
	width = 10;
	height = 10;

	nBoxes = width*height;


}

void SpatialGrid::Update()
{
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			CheckBox(i, j);
		}
	}

	for (int i = 0; i < container.size(); i++)
	{
		if (container[i].size() > 1)
		{
			AABB(i);
		}
	}

	for (int i = 0; i < container.size(); i++)
	{
		for (int j = 0; j < container[i].size(); j++)
		{
			container[i][j]->checked = false;
		}
	}
}

void SpatialGrid::CheckBox(int nWidth, int nHeight)
{
	int left = (1280 / width)*nWidth;
	int right = (1280 / width)*(nWidth + 1);

	int top = (720 / height)*nHeight;
	int bottom = (720 / height)*(nHeight + 1);

	std::vector<Object*> tempVector;

	auto itr = Game::map.Objects.begin();


	for (int k = 0; k < Game::map.Objects.size(); k++)
	{
		sf::FloatRect Obounds = (*itr)->matrix.transformRect((*itr)->ptr->getBounds());
		sf::FloatRect Mbounds(left, top, (right - left), (bottom - top));

		if (Mbounds.intersects(Obounds))
		{
			tempVector.push_back(*itr);
		}

		itr++;
	}

	container.push_back(tempVector);
}

void SpatialGrid::AABB(int i)
{
	for (int j = 0; j < container[i].size(); j++)
	{
		sf::FloatRect O1 = container[i][j]->matrix.transformRect(container[i][j]->ptr->getBounds());

		for (int k = 0; k < container[i].size(); k++)
		{
			if ((container[i][j] != container[i][k]) && (container[i][j]->checked == false) && (container[i][k]->checked==false))
			{
				sf::FloatRect O2 = container[i][k]->matrix.transformRect(container[i][k]->ptr->getBounds());

				if (O1.intersects(O2))
				{
					/*GJK gjk;

					if (gjk.Check(container[i][j], container[i][k]) == true)
					{
						Simplex simplex = gjk.simplex;

						std::cout << "touching" << std::endl;
						//EPA epa;
						//epa.Update(container[i][j], container[i][k], &simplex);
					}
					else
					{
						std::cout << "not touching" << std::endl;
					}*/

				}
			}
		}

		container[i][j]->checked = true;
	}

}