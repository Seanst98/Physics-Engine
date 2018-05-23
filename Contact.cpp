#include "stdafx.h"
#include "Contact.h"
#include "Math.h"
#include "EPA.h"

Contact::Contact()
{

}

void Contact::getPoints(Object* A, Object* B, sf::Vector2f normal, float depth)
{

	//Get the two edges
	Edge e1 = Contact::bestEdge(A, normal);
	sf::Vector2f temp = normal;
	temp.y = -temp.y;
	temp.x = -temp.x;
	Edge e2 = Contact::bestEdge(B, temp);

}

Edge Contact::bestEdge(Object* A, sf::Vector2f normal) {
	//FINDING THE FEATURES
	int index = 0;
	int max = 0;
	int c = A->GetPoints().size();
	for (int i = 0; i < A->GetPoints().size(); i++) {
		float proj = Math::Dot(A->GetPoints()[i], normal);

		if (proj > max) {
			max = proj;
			index = i;
		}
	}

	//CHOOSE BETWEEN RIGHT OR LEFT EDGE
	sf::Vector2f v = A->GetPoints()[index];
	sf::Vector2f v1;   //v.next could implement a next func
	sf::Vector2f v0;   //v.prev 

					   //Wrap around if vertex is end of array
	if (index == A->GetPoints().size() - 1) {
		v1 = A->GetPoints()[0];
	}
	else {
		v1 = A->GetPoints()[index + 1];
	}

	if (index == 0) {
		v0 = A->GetPoints()[A->GetPoints().size() - 1];
	}
	else {
		v0 = A->GetPoints()[index - 1];
	}

	sf::Vector2f l = v - v1;
	sf::Vector2f r = v - v0;

	//Normalise
	l = Math::Normalise(l);
	r = Math::Normalise(r);


	//The edge that is most perpendicular to normal will have a dot prod closer
	//to zero

	//Might be worth giving Edge its own header file but this shouldnt affect performance
	//significantly. More like a code cleanup type deal
	//Edge(maxVertex, edgeVertex1, edgeVertex2)
	Edge edge;

	if (Math::Dot(r, normal) <= Math::Dot(l, normal)) {

	}
	else {

	}
}