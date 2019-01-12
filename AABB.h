#pragma once
#include "stdafx.h"

class Object;

class AABB
{
public:

	float minX;
	float minY;
	float maxX;
	float maxY;
	float surfaceArea;
	Object *object;

	AABB() {
		minX = 0;
		minY = 0;
		maxX = 0;
		maxY = 0;
		surfaceArea = 0;
	}

	AABB(float minx, float miny, float maxx, float maxy) {
		minX = minx;
		minY = miny;
		maxX = maxx;
		maxY = maxy;

		surfaceArea = CalculateSurfaceArea();
	}

	AABB(float minx, float miny, float maxx, float maxy, float srfcarea) {
		minX = minx;
		minY = miny;
		maxX = maxx;
		maxY = maxy;

		surfaceArea = srfcarea;
	}

	bool overlaps(const AABB& other) const
	{
		return maxX > other.minX &&
			minX < other.maxX &&
			maxY > other.minY &&
			minY < other.maxY;
	}

	bool containsAABB(const AABB& other) const
	{
		return maxX >= other.maxX &&
			minX <= other.maxX &&
			maxY >= other.minY &&
			minY <= other.maxY;
	}

	bool containsPoint(const sf::Vector2f point) const
	{
		return maxX >= point.x &&
			minX <= point.x &&
			maxY >= point.y &&
			minY <= point.y;
	}

	AABB merge(const AABB& other) const
	{
		return AABB(
			std::min(minX, other.minX), std::min(minY, other.minY),
			std::max(maxX, other.maxX), std::max(maxY, other.maxY)
		);
	}

	AABB intersection(const AABB& other) const
	{
		return AABB(
			std::max(minX, other.minX), std::max(minY, other.minY),
			std::min(maxX, other.maxX), std::min(maxY, other.maxY)
		);
	}

	float CalculateSurfaceArea() {
		return (getWidth()*getHeight());
	}

	float getWidth() const { return maxX - minX; }
	float getHeight() const { return maxY - minY; }
};