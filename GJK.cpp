#include "stdafx.h"
#include "GJK.h"
#include "Map.h"
#include "Game.h"
#include "Math.h"

GJK::GJK()
{

}

bool GJK::Check(Object* O1, Object* O2)
{
	sf::Vector2f d(1, 0);

	simplex.Add(support(O1, O2, d));

	d.x = -d.x;
	d.y = -d.y;

	while (true)
	{
		simplex.Add(support(O1, O2, d));

		if (Math::Dot(simplex.getLast(), d) < 0.0)
		{
			return false;
		}
		else
		{
			if (containsOrigin(d))
			{
				return true;
			}

		}

	}
}

bool GJK::containsOrigin(sf::Vector2f& d)
{
	sf::Vector2f A = simplex.getLast();

	sf::Vector2f AO = -A;

	if (simplex.points.size() == 3)
	{

		sf::Vector2f B = simplex.points[0];
		sf::Vector2f C = simplex.points[1];

		sf::Vector2f AB = B - A;
		sf::Vector2f AC = C - A;

		sf::Vector2f ABPerp = Math::tripleProduct(AC, AB, AB);
		sf::Vector2f ACPerp = Math::tripleProduct(AB, AC, AC);

		if ((Math::Dot(ABPerp, AO)) > 0)
		{
			simplex.Remove(1);
			d = ABPerp;

			d = Math::Normalise(d);

		}
		else
		{
			if ((Math::Dot(ACPerp, AO)) > 0)
			{
				simplex.Remove(0);
				d = ACPerp;

				d = Math::Normalise(d);
			}
			else
			{
				return true;
			}
		}

	}
	else
	{
		sf::Vector2f B = simplex.points[0];
		sf::Vector2f AB = B - A;

		sf::Vector2f ABPerp = Math::tripleProduct(AB, AO, AB);

		d = ABPerp;

		d = Math::Normalise(d);
	}

	return false;

}

sf::Vector2f GJK::support(Object* shape1, Object* shape2, sf::Vector2f d) {

	std::vector<sf::Vector2f> points = shape1->GetPoints();
	sf::Vector2f p1 = GetFarthest(points, d);

	std::vector<sf::Vector2f> points2 = shape2->GetPoints();
	sf::Vector2f p2 = GetFarthest(points2, -d);

	sf::Vector2f p3 = p1-p2;

	return p3;

}


sf::Vector2f GJK::GetFarthest(std::vector<sf::Vector2f> points, sf::Vector2f d)
{
	sf::Vector2f farthest;
	float farDistance = -9999999999999;

	for (int i = 0; i < points.size(); i++)
	{
		float temp = Math::Dot(d, points[i]);

		if (temp > farDistance)
		{
			farDistance = temp;
			farthest = points[i];
		}
	}

	return farthest;
}    