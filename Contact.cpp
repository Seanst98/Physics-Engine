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

	/*sf::Vector2f temp1(2, 8);
	sf::Vector2f temp2(6, 4);
	sf::Vector2f temp3(9, 7);
	sf::Vector2f temp4(5, 11);*/
	/*sf::Vector2f temp1(8, 4);
	sf::Vector2f temp2(14, 4);
	sf::Vector2f temp3(14, 9);
	sf::Vector2f temp4(8, 9);*/
	sf::Vector2f temp1(9, 4);
	sf::Vector2f temp2(13, 3);
	sf::Vector2f temp3(14, 13);
	sf::Vector2f temp4(10, 14);
	normal.x = -0.19;
	normal.y = -0.98;

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



	//TTTTTEEEEEEEEEEEEESSSSSSTTTTTTs

	/*A->GetPoints()[0].x = 8;
	A->GetPoints()[0].y = 4;

	A->GetPoints()[1].x = 14;
	A->GetPoints()[1].y = 4;

	A->GetPoints()[2].x = 14;
	A->GetPoints()[2].y = 9;

	A->GetPoints()[3].x = 8;
	A->GetPoints()[3].y = 9;

	B->GetPoints()[0].x = 4;
	B->GetPoints()[0].y = 2;

	B->GetPoints()[1].x = 12;
	B->GetPoints()[1].y = 2;

	B->GetPoints()[2].x = 12;
	B->GetPoints()[2].y = 5;

	B->GetPoints()[3].x = 4;
	B->GetPoints()[3].y = 5;*/

	ClippedPoint x;

	clippedPoints.push_back(x);
	clippedPoints.push_back(x);

	//Get the two edges
	Edge e1 = Contact::bestEdge(C->GetPoints(), normal);
	sf::Vector2f temp = normal;
	temp.y = -temp.y;
	temp.x = -temp.x;
	Edge e2 = Contact::bestEdge(D->GetPoints(), temp);


	std::vector<sf::Vector2f> cp = Contact::clipping(e1, e2, normal);

	if (cp.size() < 2) {
		clippedPoints[0].point = cp[0];
		clippedPoints[1].point = cp[0];
	}
	else {
		clippedPoints[0].point = cp[0];
		clippedPoints[1].point = cp[1];
	}


	//COULD BOTHER WITH THIS FOR DRAWING THE NORMAL AS THE SHAPE COLLIDES
	//FOR LIVE DEBUGGING

	/*sf::VertexArray s;
	s.setPrimitiveType(sf::Lines);

	sf::Vertex t;

	t.color = sf::Color::Red;
	t.position = normal;
	t.color = sf::Color::Blue;
	t.position = normal;
	t.position.x = t.position.x + 50;
	t.position.y = t.position.y - 50;

	s.append(t);

	Game::mainWindow.draw(s);*/

}

std::vector<sf::Vector2f> Contact::clipping(Edge e1, Edge e2, sf::Vector2f normal) {

	//Need the reference edge and the incident edge
	//Reference edge is the edge most perpendicular to the separation normal
	Edge ref;
	Edge inc;

	bool flip = false;

	if (std::abs(Math::Dot((e1.B-e1.A), normal)) <= std::abs(Math::Dot((e2.B-e2.A), normal))) {
		ref = e1;
		inc = e2;
	}
	else {
		ref = e2;
		inc = e1;

		//We need to set a flag indicating that the reference 
		//and incident edge were flipped so that when we do the final
		//clip operation, we use the right edge normal
		flip = true;

	}

	sf::Vector2f refv = ref.B - ref.A;
	refv = Math::Normalise(refv);

	float o1 = Math::Dot(ref.A, refv);
	//clip the incident edge by the first
	//vertex of the reference edge

	std::vector<sf::Vector2f> cp = clip(inc.A, inc.B, refv, o1);
	//if we dont have 2 points left then fail

	if (cp.size() < 2) { return cp; }

	//clip whats left of the incident edge by the
	//second vertex of the reference edge
	//but we need to clip in the opposite direction
	//so we flip the direction and offset

	float o2 = Math::Dot(refv, ref.B);

	cp = clip(cp[0], cp[1], -refv, -o2);
	//if we dont have 2 points then fail

	if (cp.size() < 2) { return cp; }

	//get the reference edge normal
	//cross product with scalar
	//ref.cross(-1)
	//Vec = (Vec.y*scalar, Vec.x*-scalar)
	//scalar = -1

	//OK SO if anyone reads this, this part caused a lot of problems
	//The guide I used mentioned very little about this but it has
	//something to do with handedness
	//it would work for example 2 and fail the others but
	//when using the other way he describes it works for
	//every example but example 2
	//HANDEDNESS IS VERY IMPORTANT FOR CHOOSING THE CORRECT
	//ORTHOGANAL VECTOR
	//MAY NEED TO HAVE TO CHECK THAT NORMAL POINTS FROM CONVEX A TO 
	//CONVEX B WHICH COULD BE WHY THIS FAILS
	//Have to make sure it faces right way
	//pv = v-p
	//n.pv is neg then outward, pos then inward
	//make sure it points towards the incident edge

	sf::Vector2f pv = ref.B - ref.A;

	int z = -1;
	sf::Vector2f refNorm;
	refNorm.x = -1* refv.y * z;
	refNorm.y = refv.x * z;


	sf::Vector3f test;
	test.x = refv.y;
	test.y = -refv.x;
	test.z = 0;

	int a = Math::Dot(refv, inc.B-inc.A);

	if (a < 0) {
		refNorm.x = -refNorm.x;
		refNorm.y = -refNorm.y;
	}

	//if we had to flip the incident and reference edges
	//then we need to flip the reference edge normal to
	//clip properly

	/*if (flip) {
		refNorm.x = -refNorm.x;
		refNorm.y = -refNorm.y;
	}*/

	//get the largest depth
	float max = Math::Dot(refNorm, ref.max);

	//make sure the final points are not past this maximum
	//remove element using std::remove func
	/*if ((Math::Dot(refNorm, cp[0]) - max) < 0) {
		cp.erase(cp.begin());
	}
	if ((Math::Dot(refNorm, cp[1]) - max) < 0) {
		cp.erase(cp.begin() + 1);
	}*/

	float depth1 = Math::Dot(refNorm, cp[0]) - max;
	float depth2 = Math::Dot(refNorm, cp[1]) - max;

	if (depth1 < 0) {
		cp.erase(cp.begin());
	}
	if (depth2 < 0) {
		cp.erase(cp.begin() + 1);
	}

	clippedPoints[0].depth = depth1;
	clippedPoints[1].depth = depth2;

	//return the valid points
	return cp;


}

std::vector<sf::Vector2f> Contact::clip(sf::Vector2f v1, sf::Vector2f v2, sf::Vector2f n, float o) {

	//clips the line segment points v1, v2
	//if they are past o along n

	std::vector<sf::Vector2f> cp;
	float d1 = Math::Dot(n, v1) - o;
	float d2 = Math::Dot(n, v2) - o;

	//if either point is past o along n
	//then we can keep the point
	if (d1 >= 0) {
		cp.push_back(v1);
	}
	if (d2 >= 0) {
		cp.push_back(v2);
	}
	
	//finally we need to check if they
	//are on opposing sides so that we can
	//compute the correct point
	if ((d1*d2) < 0) {
		//if they are on different sides of the
		//offset, d1 and d2 2ill be a (+) * (-)
		//and will yield a (-) and therefore be
		// < 0
		//get the vector for the edge we are clipping
		sf::Vector2f e = v2 - v1;

		//compute the location along e
		float u = d1 / (d1 - d2);
		e = e * u;
		e = e + v1;

		//add the point
		cp.push_back(e);
	}

	return cp;
}

Edge Contact::bestEdge(std::vector<sf::Vector2f> A, sf::Vector2f normal) {
	//FINDING THE FEATURES
	int index = 0;
	int max = -999999;
	//int c = A->GetPoints().size();
	int c = A.size();
	//for (int i = 0; i < A->GetPoints().size(); i++) {
	for (int i = 0; i < A.size(); i++) {

		//float proj = Math::Dot(A->GetPoints()[i], normal);
		float proj = Math::Dot(A[i], normal);

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

					   //Wrap around if vertex is end of array
	/*if (index == A->GetPoints().size() - 1) {
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
	}*/

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


	//The edge that is most perpendicular to normal will have a dot prod closer
	//to zero

	//Might be worth giving Edge its own header file but this shouldnt affect performance
	//significantly. More like a code cleanup type deal
	//Edge(maxVertex, edgeVertex1, edgeVertex2)
	Edge edge;

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