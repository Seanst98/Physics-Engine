#include "stdafx.h"
#include "Contact.h"
#include "Math.h"
#include "EPA.h"
#include "Game.h"

Contact::Contact()
{

}

void Contact::getPoints(Object* C, Object* D, sf::Vector2f normal, float depth)
{
	std::vector<sf::Vector2f> A;
	std::vector<sf::Vector2f> B;

	normal.x = 0;
	normal.y = -1;

	/*sf::Vector2f temp1(8, 4);
	sf::Vector2f temp2(14, 4);
	sf::Vector2f temp3(14, 9);
	sf::Vector2f temp4(8, 9);*/

	sf::Vector2f temp1(2, 8);
	sf::Vector2f temp2(6, 4);
	sf::Vector2f temp3(9, 7);
	sf::Vector2f temp4(5, 11);

	/*sf::Vector2f temp1(9, 4);
	sf::Vector2f temp2(13, 3);
	sf::Vector2f temp3(14, 13);
	sf::Vector2f temp4(10, 14);
	normal.x = -0.19;
	normal.y = -0.98;*/

	A.push_back(temp1);
	A.push_back(temp2);
	A.push_back(temp3);
	A.push_back(temp4);


	sf::Vector2f temp11(4, 2);
	sf::Vector2f temp12(12, 2);
	sf::Vector2f temp13(12, 5);
	sf::Vector2f temp14(4, 5);
	B.push_back(temp11);
	B.push_back(temp12);
	B.push_back(temp13);
	B.push_back(temp14);


	//Get the two edges
	Edge e1 = Contact::bestEdge(A, normal);
	Edge e2 = Contact::bestEdge(B, -normal);

	clippedPoints = Contact::clipping(e1, e2, normal);


	sf::CircleShape circle;

	for (int i = 0; i < clippedPoints.size(); i++) {
		circle.setRadius(10);
		sf::Vector2f temp(circle.getRadius(), circle.getRadius());
		//circle.setOrigin(circle.getOrigin() + temp);
		circle.setPosition(clippedPoints[i].point - temp);
		sf::Color c(0, 0, 255);

		circle.setFillColor(c);

		Game::mainWindow.draw(circle);
	}

}

std::vector<ClippedPoint> Contact::clipping(Edge e1, Edge e2, sf::Vector2f normal) {

	Edge ref, inc;
	bool flip = false;

	if (std::abs(Math::Dot(e1.B - e1.A, normal)) <= std::abs(Math::Dot(e2.B - e2.A, normal))) {
		ref = e1;
		inc = e2;
	}
	else {
		ref = e2;
		inc = e1;
		flip = true;
	}

	sf::Vector2f refv = ref.B - ref.A;
	refv = Math::Normalise(refv);

	double o1 = Math::Dot(refv, ref.A);

	std::vector<ClippedPoint> cp = clip(inc.A, inc.B, refv, o1);

	double o2 = Math::Dot(refv, ref.B);

	cp = clip(cp[0].point, cp[1].point, -refv, -o2);

	sf::Vector2f refNorm = Math::Cross(refv, -1);


	if (flip) {
		refNorm = -refNorm;
	}

	double max = Math::Dot(refNorm, ref.max);
	
	cp[0].depth = Math::Dot(refNorm, cp[0].point) - max;
	cp[1].depth = Math::Dot(refNorm, cp[1].point) - max;

	if (cp[1].depth < 0) {
		cp.erase(cp.begin() + 1);
	}
	if (cp[0].depth < 0) {
		cp.erase(cp.begin());
	}


	if (cp.size() != 0) {
		sf::Vector2f temp(cp[0].point);
		temp.x = temp.x / 2;
		temp.y = temp.y / 2;
		sf::RectangleShape line(sf::Vector2f(150, 5));
		line.setPosition(temp);
		sf::Color g(0, 255, 0);
		line.setFillColor(g);

		float angle = Math::Dot(refNorm, sf::Vector2f(1, 1)) / (Math::Magnitude(refNorm) * Math::Magnitude(sf::Vector2f(1, 1)));

		line.rotate(angle*180);

		Game::mainWindow.draw(line);
	}


	return cp;
}

std::vector<ClippedPoint> Contact::clip(sf::Vector2f v1, sf::Vector2f v2, sf::Vector2f n, float o) {
	std::vector<ClippedPoint> cp;

	double d1 = Math::Dot(n, v1) - o;
	double d2 = Math::Dot(n, v2) - o;

	if (d1 >= 0) {
		ClippedPoint a;
		a.point = v1;
		a.depth = 0;
		cp.push_back(a);
	}
	if (d2 >= 0) {
		ClippedPoint a;
		a.point = v2;
		a.depth = 0;
		cp.push_back(a);
	}

	if (d1*d2 < 0) {
		sf::Vector2f e = v2 - v1;

		double u = d1 / (d1 - d2);

		e.x = e.x * u;
		e.y = e.y * u;

		e = e + v1;

		ClippedPoint a;
		a.point = e;
		a.depth = 0;

		cp.push_back(a);

	}

	return cp;

}

Edge Contact::bestEdge(std::vector<sf::Vector2f> A, sf::Vector2f normal) {
	//FINDING THE FEATURES
	int index = 0;
	int max = -999999;
	for (int i = 0; i < A.size(); i++) {

		//float proj = Math::Dot(A->GetPoints()[i], normal);
		float proj = Math::Dot(normal, A[i]);

		if (proj > max) {
			max = proj;
			index = i;
		}
	}

	//CHOOSE BETWEEN RIGHT OR LEFT EDGE
	//sf::Vector2f v = A->GetPoints()[index];
	sf::Vector2f v = A[index];
	sf::Vector2f v1;   //v.next could implement a next func
	sf::Vector2f v0;   //v.prev 

	if (index == A.size() - 1) {
		v1 = A[0];
	}
	else {
		v1 = A[index + 1];
	}

	if(index == 0) {
		v0 = A[A.size() - 1];
	}
	else {
		v0 = A[index - 1];
	}

	sf::Vector2f l = v - v1;
	sf::Vector2f r = v - v0;

	//Normalise
	l = Math::Normalise(l);
	r = Math::Normalise(r);

	Edge edge;

	float a = Math::Dot(r, normal);
	float b = Math::Dot(l, normal);

	if (Math::Dot(r, normal) <= Math::Dot(l, normal)) {
		
		edge.A = v0;
		edge.B = v;
		edge.max = v;
		return edge;

	}
	else {

		edge.A = v;
		edge.B = v1;
		edge.max = v;
		return edge;

	}
}