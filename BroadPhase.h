#pragma once
#include "AABB.h"
#include <list>

struct Ray2
{
	sf::Vector2f pos;
	sf::Vector2f dir;
};

struct RayCastResult
{
	bool hit;
	Object *object;
	sf::Vector2f position;
	sf::Vector2f normal;
};

class BroadPhase
{
public:

	//adds a new AABB to the broadphase
	virtual void Add(AABB *aabb) = 0;

	//updates broadphase to react to changes to AABB
	virtual void Update() = 0;

	//returns a list of possibly colliding objects
	virtual const std::list<std::pair<Object*, Object*>> &ComputePairs(void) = 0;

	//returns an object that collides with a point
	//returns null if no object exists
	virtual Object *Pick(const sf::Vector2f &point) const = 0;

	//returns a list of objects whos AABBs collide with a query AABB
	virtual void Query(const AABB &aabb, std::vector<Object*> &output) const = 0;

	//result contains the first object the ray hits
	//result contains null if no object is hit
	virtual RayCastResult RayCast(const Ray2 &ray) const = 0;

};