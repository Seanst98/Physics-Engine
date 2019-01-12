#include "stdafx.h"
#include "Resolution.h"
#include "Math.h"
#include "Contact.h"
#include <algorithm>

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

	float restitution = 0.8;
	float closingSpeed;
	sf::Vector2f closingSpeedtemp;
	closingSpeedtemp = B->GetCentre() - A->GetCentre();
	closingSpeed = -(Math::Dot((B->velocity - A->velocity), closingSpeedtemp) / Math::Magnitude(closingSpeedtemp));
	if (closingSpeed < 1) {
		restitution = 0;
	}

	//REDO OF ANGULAR CALCULATION

	sf::Vector2f rA = cp[0].point - A->GetCentre();
	sf::Vector2f rB = cp[0].point - B->GetCentre();



	float wA = A->GetWidthHeight().x;
	float hA = A->GetWidthHeight().y;
	float IA = A->mass*((hA*hA) + (wA * wA)) / 12;

	float wB = B->GetWidthHeight().x;
	float hB = B->GetWidthHeight().y;
	float IB = B->mass*((hB*hB) + (wB * wB)) / 12;


	sf::Vector2f va = A->velocity + Math::Cross(A->Rvelocity, rA);
	sf::Vector2f vb = B->velocity + Math::Cross(B->Rvelocity, rB);

	float j = -(1 + restitution)*(Math::Dot(va - vb, normal));

	//float temp = ((1 / A->mass) + (1 / B->mass));
	float temp = A->GetInvMass() + B->GetInvMass();

	double temp1 = (Math::Cross(rA, normal) * Math::Cross(rA, normal)) / IA;
	double temp2 = (Math::Cross(rB, normal) * Math::Cross(rB, normal)) / IB;

	j = j / (temp + temp1 + temp2);


	//A->velocity += (j / (A->mass))*normal;
	//B->velocity -= (j / (B->mass))*normal;
	A->velocity += (j*A->GetInvMass()*normal);
	B->velocity -= (j*B->GetInvMass()*normal);

	A->Rvelocity += Math::Cross(rA, j*normal) / IA;
	B->Rvelocity -= Math::Cross(rB, j*normal) / IB;


	//FRICTION
	sf::Vector2f tangentVelocity = relV - (Math::Dot(relV, normal) * normal);
	sf::Vector2f tangentVector = Math::Normalise(tangentVelocity);

	//CORRECTIONS
	/*float penAllow = 0.001;
	float percent = 0.2;

	float q = std::max(cp[0].depth - penAllow, 0.0f);
	float r = (1 / A->mass) + (1 / B->mass);

	sf::Vector2f correction = (q/r)*percent*normal;


	float rot = std::fmod(A->rotation, 360);

	rot = 360 - rot;

	A->matrix.rotate(rot, A->GetLocalCentre());

	A->matrix.translate(-(1 / A->mass)*correction);

	A->matrix.rotate(A->rotation, A->GetLocalCentre());

	rot = std::fmod(B->rotation, 360);

	rot = 360 - rot;

	B->matrix.rotate(rot, B->GetLocalCentre());

	B->matrix.translate((1 / B->mass)*correction);

	B->matrix.rotate(B->rotation, B->GetLocalCentre());*/

}