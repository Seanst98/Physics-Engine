#include "stdafx.h"
#include "Resolution.h"
#include "Math.h"
#include "Contact.h"

Resolution::Resolution()
{

}

void Resolution::Update(Object* A, Object* B, std::vector<ClippedPoint> cp, sf::Vector2f normal)
{
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
	sf::Vector2f impulse;

	j = -(1 + restitution)*contactVel;
	j /= (1 / A->mass) + (1 / B->mass);

	//float impulse = (-(1 + restitution)*(relVdotn)) / ((1 / A->mass) + (1 / B->mass));
	impulse = j * normal;

	A->velocity -= impulse / A->mass;
	B->velocity += impulse / B->mass;

	//Angular momentum impulse 
	//r = vector from centre of mass to a point on the body (contact point)
	sf::Vector2f rA = cp[0].point - A->GetCentre();
	sf::Vector2f rB = cp[0].point - B->GetCentre();

	sf::Vector2f test = A->GetCentre();
	sf::Vector2f test1 = B->GetCentre();

	//rA = Math::Normalise(rA);
	//rB = Math::Normalise(rB);

	//Velocity of point on body relative to centre


	sf::Vector2f VpointA = A->velocity + Math::Cross(A->Rvelocity, rA);

	sf::Vector2f VpointB = B->velocity + Math::Cross(B->Rvelocity, rB);

	//WOULD BE WORTH INVESTING IN A 2D CROSS MATH FUNC
	float rAcn = Math::Cross(rA, normal);
	float rBcn = Math::Cross(rB, normal);

	//Inertia tensor
	float ITA = 1;
	float ITB = 1;

	float contactVelR = Math::Dot(VpointB - VpointA, normal);
	j = -(1 + restitution)*contactVelR;
	j /= (1 / A->mass) + (1 / B->mass) + ((rAcn*rAcn) / ITA) + ((rBcn*rBcn) / ITB);

	impulse = j * normal;

	A->Rvelocity -= (1 / ITA)*(Math::Cross(rA, impulse));

	B->Rvelocity += (1 / ITA)*(Math::Cross(rB, impulse));








}