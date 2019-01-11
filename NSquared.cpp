#include <list>
#include "Object.h"
#include "NSquared.h"
#include "AABB.h"

const std::list<std::pair<Object*, Object*>> &NSquared::ComputePairs()
{
	m_pairs.clear();

	//outer loop
	auto end = m_aabbs.end();
	for (auto i = m_aabbs.begin(); i != end; ++i)
	{

		//inner loop
		auto jStart = i;
		for (auto j = ++jStart; j != end; ++j)
		{
			AABB *aabbA = *i;
			AABB *aabbB = *j;
			Object *objectA = aabbA->Object();
			Object *objectB = aabbB->Object();

			//skip same body collision
			if ()
		}
	}
}