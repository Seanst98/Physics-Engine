#pragma once
#include "stdafx.h"
#include "Object.h"
#include "Contact.h"

class Resolution
{
public:
	Resolution();

	void Update(Object*, Object*, std::vector<ClippedPoint>, sf::Vector2f);

};
