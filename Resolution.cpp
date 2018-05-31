#include "stdafx.h"
#include "Resolution.h"
#include "Math.h"
#include "Contact.h"

Resolution::Resolution()
{

}

void Resolution::Update(Object* A, Object* B, std::vector<ClippedPoint> cp, sf::Vector2f normal)
{

	/*for (int i = 0; i < cp.size(); i++) {
		sf::Vector2f relV = B->velocity - A->velocity;

		float contactVel = Math::Dot(relV, normal);


		if (contactVel > 0) {
			return;
		}

		//NEWTONS LAW OF RESTITUTION
		//velBefore * restitution = velAfter

		float restitution = 0.5;

		//IMPULSE
		//instantaneous change in velocity
		//velocityNew = VelocityOld * Impulse
		//velocityNew = velocityOld + Imupulse(Direction) 
		//^^ allows for pointing vector in one direction or another

		//sf::Vector2f velNew = velOld + impulse(direction);





		//MOMENTUM
		//momentum = mass * velocity
		//impulse = momentumAfter - momentumBefore

		float j;

		float temp;
		float temp1;
		float temp2;

		j = -(1 + restitution)*contactVel;
		j /= (1 / A->mass) + (1 / B->mass);

		//float impulse = (-(1 + restitution)*(relVdotn)) / ((1 / A->mass) + (1 / B->mass));
		sf::Vector2f impulse = j * normal;

		//A->velocity -= impulse / A->mass;
		//B->velocity += impulse / B->mass;

		//REDO OF ANGULAR CALCULATION

		sf::Vector2f rA = cp[i].point - A->GetCentre();
		sf::Vector2f rB = cp[i].point - B->GetCentre();



		float wA = A->GetPoints()[2].x - A->GetPoints()[0].x;
		float hA = A->GetPoints()[2].y - A->GetPoints()[0].y;
		float IA = A->mass*((hA*hA) + (wA * wA)) / 12;

		float wB = B->GetPoints()[2].x - B->GetPoints()[0].x;
		float hB = B->GetPoints()[2].y - B->GetPoints()[0].y;
		float IB = B->mass*((hB*hB) + (wB * wB)) / 12;



		j = -(1 + restitution)*(Math::Dot(relV, normal));

		temp = Math::Dot(normal, normal)*((1 / A->mass) + (1 / B->mass));

		//Something wrong with temp1 and temp2
		//Maybe should reserve negative sign after squaring as temp1 and temp2 allow for cancelling

		temp1 = ((Math::Dot(Math::Perpendicular(rA), normal)) * (Math::Dot(Math::Perpendicular(rA), normal))) / IA;
		temp2 = ((Math::Dot(Math::Perpendicular(rB), normal)) * (Math::Dot(Math::Perpendicular(rB), normal))) / IB;

		j = j / (temp + temp1 + temp2);

		A->velocity -= (j / (A->mass))*normal;
		B->velocity += (j / (B->mass))*normal;

		A->Rvelocity -= (Math::Dot((Math::Perpendicular(rA)), j * normal)) / IA;
		B->Rvelocity += (Math::Dot((Math::Perpendicular(rB)), j * normal)) / IB;
	}*/


}