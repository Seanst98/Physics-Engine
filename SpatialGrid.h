#pragma once
#include "stdafx.h"
#include "Object.h"

class SpatialGrid
{
public:
	SpatialGrid();

	void Update();
	void AABB(int i);

	void CheckBox(int, int);

	int nBoxes;

	int height;
	int width;

	std::vector<std::vector<Object*>> container;
};