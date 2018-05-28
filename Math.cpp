#include "stdafx.h"
#include "Math.h"

sf::Vector2f Math::tripleProduct(sf::Vector2f A, sf::Vector2f B, sf::Vector2f C)
{

	sf::Vector2f temp;
	sf::Vector2f temp2;
	float dot1;
	float dot2;

	dot1 = Dot(A, C);
	dot2 = Dot(C, B);

	temp.x = dot1 * B.x;
	temp.y = dot1 * B.y;

	temp2.x = dot2 * A.x;
	temp2.y = dot2 * A.y;

	sf::Vector2f temp3;

	temp3 = temp - temp2;

	if ((temp3.x == 0) && (temp3.y == 0)) { temp3.x = 1; temp3.y = 1; }

	return temp3;

}

float Math::Magnitude(sf::Vector2f v) {
	return (std::sqrt((v.x * v.x) + (v.y*v.y)));
}

sf::Vector2f Math::Normalise(sf::Vector2f d)
{
	double magnitude = (d.x * d.x) + (d.y*d.y);
	magnitude = std::sqrt(magnitude);

	d.x = d.x / magnitude;
	d.y = d.y / magnitude;

	return d;
}

float Math::Dot(sf::Vector2f A, sf::Vector2f B)
{
	return (A.x * B.x) + (A.y * B.y);
}

float Math::Cross(sf::Vector2f A, sf::Vector2f B)
{
	return ((A.x * B.y) - A.y*B.x);
}

sf::Vector2f Math::Cross(sf::Vector2f A, float b) {
	sf::Vector2f ret;

	ret.x = b * A.y;
	ret.y = -b * A.x;

	return ret;
}

sf::Vector2f Math::Cross(float a, sf::Vector2f B) {
	sf::Vector2f ret;

	ret.x = -a * B.y;
	ret.y = a * B.x;

	return ret;
}

sf::Vector2f Math::GetFarthest(std::vector<sf::Vector2f> points, sf::Vector2f d)
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