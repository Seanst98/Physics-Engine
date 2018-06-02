#include "stdafx.h"
#include "Resolution.h"
#include "Math.h"
#include "Contact.h"

Resolution::Resolution()
{

}

void Resolution::Update(Object* A, Object* B, std::vector<ClippedPoint> cp, sf::Vector2f normal)
{

	//C: JV + b = 0
	//V (6 by 1) velocity vector
	//J (1 by 6) Jacobian
	//b is only present when wanting to introduce energy

	//POSSIBLY WORTH INVESTING IN MATRIX CLASS

	if (cp.size() == 0) {
		return;
	}

	if (cp.size() == 2) {
		cp[0].point = cp[1].point + cp[0].point;
		cp[0].point.x = cp[0].point.x / 2;
		cp[0].point.y = cp[0].point.y / 2;
	}

	sf::Vector2f relV = B->velocity - A->velocity;

	float contactVel = Math::Dot(relV, normal);


	if (contactVel > 0) {
		return;
	}

	//NEWTONS LAW OF RESTITUTION
	//velBefore * restitution = velAfter

	float restitution = 0.5;

	//REDO OF ANGULAR CALCULATION

	sf::Vector2f rA = cp[0].point - A->GetCentre();
	sf::Vector2f rB = cp[0].point - B->GetCentre();



	float wA = A->GetPoints()[2].x - A->GetPoints()[0].x;
	float hA = A->GetPoints()[2].y - A->GetPoints()[0].y;
	float IA = A->mass*((hA*hA) + (wA * wA)) / 12;

	float wB = B->GetPoints()[2].x - B->GetPoints()[0].x;
	float hB = B->GetPoints()[2].y - B->GetPoints()[0].y;
	float IB = B->mass*((hB*hB) + (wB * wB)) / 12;



	float j = -(1 + restitution)*(Math::Dot(relV, normal));

	float temp = Math::Dot(normal, normal)*((1 / A->mass) + (1 / B->mass));

	//Something wrong with temp1 and temp2
	//Maybe should reserve negative sign after squaring as temp1 and temp2 allow for cancelling

	double temp1 = ((Math::Dot(Math::Perpendicular(rA), normal)) * (Math::Dot(Math::Perpendicular(rA), normal))) / IA;
	double temp2 = ((Math::Dot(Math::Perpendicular(rB), normal)) * (Math::Dot(Math::Perpendicular(rB), normal))) / IB;

	j = j / (temp + temp1 + temp2);


	A->velocity -= (j / (A->mass))*normal;
	B->velocity += (j / (B->mass))*normal;

	A->Rvelocity += (Math::Dot((Math::Perpendicular(rA)), j * normal)) / IA;
	B->Rvelocity -= (Math::Dot((Math::Perpendicular(rB)), j * normal)) / IB;


}