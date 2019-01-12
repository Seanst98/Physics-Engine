#include "stdafx.h"
#include <list>
#include "Object.h"
#include "NSquared.h"
#include "AABB.h"

std::list<std::pair<Object*, Object*>> &NSquared::ComputePairs()
{
	m_pairs.clear();

	//outer loop
	auto end = m_aabbs.end();
	for (auto i = m_aabbs.begin(); i != end; ++i)
	{
		//***************************************
		//TODO: NEED A WAY TO UPDATE AABBS AS THEY
		//CURRENTLY DON'T UPDATE THEIR POSITION AND 
		//SO THEY WON'T BE DETECTED WHEN COLLIDING
		//***************************************

		//inner loop
		auto jStart = i;
		for (auto j = ++jStart; j != end; ++j)
		{
			AABB *aabbA = *i;
			AABB *aabbB = *j;
			Object *objectA = aabbA->object;
			Object *objectB = aabbB->object;

			aabbA = aabbA->object->aabb;
			aabbB = aabbB->object->aabb;

			//skip same body collision
			if (objectA == objectB)
				continue;

			std::cout << "Max Y: " << aabbA->maxY << std::endl;
			std::cout << "Max Y: " << aabbB->maxY << std::endl;
			
			std::cout << "Min Y: " << aabbA->minY << std::endl;
			std::cout << "Min Y: " << aabbB->minY << std::endl;

			//std::cout << "x1: " << objectA->GetPoints()[0].x << std::endl;
			//std::cout << "y1: " << objectA->GetPoints()[0].y << std::endl;

			//std::cout << "x2: " << objectB->GetPoints()[0].x << std::endl;
			//std::cout << "y2: " << objectB->GetPoints()[0].y << std::endl;
			//add object pair
			if (aabbA->overlaps(*aabbB))
			{
				std::cout << "The AABBs intersect" << std::endl;
				m_pairs.push_back(std::make_pair(aabbA->object, aabbB->object));
			}

		}
	}

	return m_pairs;
}

Object *NSquared::Pick(const sf::Vector2f &point) const
{
	for (auto &aabb : m_aabbs)
	{
		if (aabb->containsPoint(point))
		{
			return aabb->object;
		}
	}

	//no collider found
	return nullptr;
}

void NSquared::Query(const AABB &aabb, std::vector<Object*> &out) const
{
	for (auto &objectAABB : m_aabbs)
	{
		if (objectAABB->overlaps(aabb))
		{
			out.push_back(objectAABB->object);
		}
	}
}

RayCastResult NSquared::RayCast(const Ray2 &ray) const
{
	//test AABBs for candidates
	std::vector<Object*> candidateList;
	candidateList.reserve(m_aabbs.size());

	for (AABB *aabb : m_aabbs)
	{
		/*if (aabb->TestRay(ray))
		{
			candidateList.push_back(aabb->object);
		}*/
	}

	//struct for storing ray-collider test results
	struct ResultEntry
	{
		Object *object;
		float t;
		sf::Vector2f normal;

		bool operator<(const ResultEntry &rhs) const
		{
			//smaller t = closer
			return t > rhs.t;
		}
	};

	//test actual objects
	std::vector<ResultEntry> resultList;
	resultList.reserve(candidateList.size());

	for (Object *object : candidateList)
	{
		//hit point = ray.pos + t * ray.dir
		float t;
		sf::Vector2f normal;
		/*if (object->TestRay(ray, t, normal))
		{
			ResultEntry entry = {object, t, normal };
			resultList.push_back(entry);
		}*/
	}

	//sort the result list
	std::sort(resultList.begin(), resultList.end());

	RayCastResult result;
	if (!resultList.empty())
	{
		//the first result entry is the closest one
		ResultEntry &entry = resultList.front();
		result.hit = true;
		result.object = entry.object;
		result.normal = entry.normal;
		result.position = ray.pos + entry.t * ray.dir;
	}
	else {
		result.hit = false;
	}

	return result;
}