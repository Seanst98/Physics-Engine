#pragma once
#include "stdafx.h"
#include "Object.h"
#include "ResourceManager.h"
#include "Game.h"

Object::Object(std::string name)
{
	//ptr = ResourceManager::Get(name);
}

void Object::Update()
{
	sf::Transform rotation;
	rotation.rotate(180*ET);

	matrix.combine(rotation);
}