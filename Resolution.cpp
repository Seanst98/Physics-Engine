#include "stdafx.h"
#include "Resolution.h"
#include "Math.h"
#include "Contact.h"
#include <algorithm>
#include "Game.h"

Resolution::Resolution()
{

}

void Resolution::Update(Object* A, Object* B, std::vector<ClippedPoint> cp, sf::Vector2f normal)
{

	//***********************************
	//SEQUENTIAL IMPULSE
	//***********************************

	//Velocity constraint:
	// Cd : JV + b = 0

	float constraint = 0;
	int iterations = 0;

	if (cp.size() == 0) {
		return;
	}

	std::cout << cp.size() << std::endl;

	float normalImpulseSum = 0;
	float normalImpulseSumCopy = 0;

		constraint = 0;

		float b = 0;
		sf::Vector2f rA;
		sf::Vector2f rB;

		if (cp.size() == 1) {
			rA = cp[0].point - A->GetCentre();
			rB = cp[0].point - B->GetCentre();
		}
		else
		{
			rA = cp[0].point - A->GetCentre();
			rB = cp[1].point - B->GetCentre();
		}

		sf::Vector2f PA;
		sf::Vector2f PB;

		PA = A->GetCentre() + rA;
		PB = B->GetCentre() + rB;

		float e = 1;
		float depth = Math::Dot((PB - PA), normal);
		b = (-0.2 / ET)*depth;

		rA = Math::Normalise(rA);
		rB = Math::Normalise(rB);

		b += e * Math::Dot((-A->velocity - (Math::Cross(A->Rvelocity*3.14/180, rA))) + (B->velocity + (Math::Cross(B->Rvelocity*3.14/180, rB))), normal);

		std::vector<float> J;
		J.push_back(-normal.x);
		J.push_back(-normal.y);
		J.push_back(Math::Cross(-rA, normal));
		J.push_back(normal.x);
		J.push_back(normal.y);
		J.push_back(Math::Cross(rB, normal));

		std::vector<float> V;
		V.push_back(A->velocity.x);
		V.push_back(A->velocity.y);
		V.push_back(A->Rvelocity*3.14/180);
		V.push_back(B->velocity.x);
		V.push_back(B->velocity.y);
		V.push_back(B->Rvelocity*3.14/180);

		std::vector<float> M;
		M.push_back(A->mass);
		M.push_back(A->mass);
		float wA = A->GetWidthHeight().x / 2;
		float hA = A->GetWidthHeight().y / 2;
		float IA = (A->mass*((hA*hA) + (wA * wA))) / 12;
		M.push_back(IA);

		float wB = B->GetWidthHeight().x / 2;
		float hB = B->GetWidthHeight().y / 2;
		float IB = (B->mass*((hB*hB) + (wB * wB))) / 12;
		//M.push_back(A->inertiaTensor);
		M.push_back(B->mass);
		M.push_back(B->mass);
		M.push_back(IB);
		//M.push_back(A->inertiaTensor);


		float lambda = 0;

		for (int i = 0; i < 6; ++i) {
			//std::cout << V[i] << std::endl;
			lambda += J[i] * V[i];
		}

		//std::cout << "JV: " << lambda << std::endl;

		lambda += b;
		//std::cout << "+ b: " << lambda << std::endl;

		lambda = -lambda;

		//std::cout << "Minus: " << lambda << std::endl;
		std::vector<float> temp;
		temp.resize(J.size());


		for (int j = 0; j < 6; ++j) {
			temp[j] = J[j] * (1 / M[j]);
		}

		float temp2 = 0;

		for (int l = 0; l < 6; ++l) {
			temp2 += J[l] * temp[l];
		}

		lambda = lambda / temp2;

		normalImpulseSumCopy = normalImpulseSum;
		normalImpulseSum += lambda;
		if (normalImpulseSum < 0) {
			normalImpulseSum = 0;
		}

		std::vector<float> temp3;
		temp3.resize(J.size());

		for (int m = 0; m < 6; ++m) {
			temp3[m] = (1 / M[m])*J[m];
			temp3[m] = temp3[m] * normalImpulseSum;
		}


		normalImpulseSum = normalImpulseSum - normalImpulseSumCopy;

		A->velocity.x += temp3[0];
		A->velocity.y += temp3[1];
		A->Rvelocity += temp3[2] * 180 / 3.14;
		B->velocity.x += temp3[3];
		B->velocity.y += temp3[4];
		B->Rvelocity += temp3[5] * 180 / 3.14;

		//std::cout << "lambda: " << lambda << std::endl;
		//std::cout << "Adding to A: " << temp3[0] << std::endl;
		//std::cout << "A before: " << A->velocity.x << std::endl;
		//std::cout << "B before: " << B->velocity.x << std::endl;
		//std::cout << "A after: " << A->velocity.x << std::endl;
		//std::cout << "B after: " << B->velocity.x << std::endl;
}