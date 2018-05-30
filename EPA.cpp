#include "stdafx.h"
#include "EPA.h"
#include "Math.h"

EPA::EPA()
{

}

void EPA::Update(Object* A, Object* B, Simplex* simplex)
{

	calcWinding(simplex);

	while (true)
	{

		Edge e = ClosestEdge(*simplex);

		sf::Vector2f p = support(A, B, e.normal);


		double d = Math::Dot(p, e.normal);

		if ((d - e.distance) <= 0.01) // the tolerance should be something positive close to zero (ex. 0.00001)
		{
			normal = e.normal;
			depth = d;

			break;
		}
		else   //We have not reached the edge of the Minkowski Difference so continue adding point
		{
			simplex->Insert(p, e.index);
		}
	}

}

Edge EPA::ClosestEdge(Simplex simplex)
{
	Edge closest;

	closest.distance = 99999999999999;

	int j = 0;

	for (int i = 0; i < simplex.points.size(); i++)
	{

		if ((i + 1) == simplex.points.size()) {
			j = 0;
		}
		else
		{
			j = i + 1;
		}

		sf::Vector2f A = simplex.points[i];
		sf::Vector2f B = simplex.points[j];

		sf::Vector2f e = B - A;

		sf::Vector2f OA = A;

		sf::Vector2f n;

		if (winding == "Clockwise") {

			n.x = e.y;
			n.y = -e.x;

		}
		else
		{
			n.x = -e.y;
			n.y = e.x;
		}
		//sf::Vector2f n = Math::tripleProduct(e, OA, e);
		//Used to use tripleProduct, however, that can cause issues with normalisation
		//As normalising with zero is dividing by zero
		//Winding of simplex is calculated at beginning and used instead

		n = Math::Normalise(n);
 
		double d = Math::Dot(n, A);

		if (d < closest.distance)
		{
			closest.distance = d;
			closest.normal = n;
			closest.index = j;

		}

	}
	
	return closest;
}


void EPA::calcWinding(Simplex* simplex) {
	//POSITIVE IMPLIES CLOCKWISE
	//NEGATIVE IMPLIES COUNTER CLOCKWISE

	int sum = 0;

	for (int i = 0; i < simplex->points.size()-1; i++) {
		float temp = (simplex->points[i + 1].x - simplex->points[i].x);
		float temp2 = (simplex->points[i + 1].y - simplex->points[i].y);
		float temp3 = temp * temp2;

		sum = sum + temp3;
	}

	if (sum > 0) {
		winding = "Clockwise";
	}
	else
	{
		winding = "AntiClockwise";
	}
}