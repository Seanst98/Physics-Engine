#pragma once
#include "BroadPhase.h"

class NSquared : public BroadPhase
{
public:

	std::list<AABB*> m_aabbs;

	virtual void Add(AABB *aabb)
	{
		m_aabbs.push_back(aabb);
	}

	virtual void Update()
	{
		//do nothing
	}

	virtual std::list<std::pair<Object*, Object*>> &ComputePairs(void);
	virtual Object *Pick(const sf::Vector2f &point) const;
	virtual void Query(const AABB &aabb, std::vector<Object*> &out) const;
	virtual RayCastResult RayCast(const Ray2 &ray) const;

private:

	//std::list<AABB*> m_aabbs;
	std::list<std::pair<Object*, Object*>> m_pairs;


};