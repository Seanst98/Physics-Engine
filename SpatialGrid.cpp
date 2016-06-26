#include "stdafx.h"
#include "SpatialGrid.h"
#include "Map.h"
#include "Game.h"

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

}

void SpatialGrid::CheckBox(int nWidth, int nHeight)
{
	int left = (1280 / width)*nWidth;
	int right = (1280 / width)*(nWidth + 1);

	int top = (1280 / height)*nHeight;
	int bottom = (1280 / height)*(nHeight + 1);

	auto itr = Game::map.Objects.begin();

	/*for (int i = 0; i < Game::map.Objects.size(); i++)
	{
		if (itr->matrix.transformPoint(itr->ptr->)
	}*/

}