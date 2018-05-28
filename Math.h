#pragma once
#include "stdafx.h"

static class Math
{

public:

	static sf::Vector2f tripleProduct(sf::Vector2f, sf::Vector2f, sf::Vector2f);
	static float Dot(sf::Vector2f, sf::Vector2f);
	static sf::Vector2f Normalise(sf::Vector2f);
	static float Magnitude(sf::Vector2f);
	static float Cross(sf::Vector2f, sf::Vector2f);
	static sf::Vector2f Cross(sf::Vector2f, float);
	static sf::Vector2f Cross(float, sf::Vector2f);
	static sf::Vector2f GetFarthest(std::vector<sf::Vector2f>, sf::Vector2f);

};
