#pragma once
#include "stdafx.h"
#include "Game.h"
#include "GJK.h"
#include "EPA.h"
#include "Contact.h"
#include "Resolution.h"

void Game::Start()
{
	mainWindow.create(sf::VideoMode(1280, 720, 32), "Physics");
	view.setCenter(1280 / 2, 720 / 2);
	view.setSize(1280, 720);
	mainWindow.setView(view);

	gameState = Playing;

	font.loadFromFile("fonts/consola.ttf");

	fpsText.setColor(sf::Color::Red);
	fpsText.setPosition(10, 30);
	fpsText.setFont(font);

	//noobjects = 0;
	fpsavg = 0;

	resManager.DefineTriangle();
	resManager.DefineQuad();
	resManager.DefinePentagon();
	resManager.DefinePrzemekShape();

	Object *object = new Object("quad", "block");

	object->matrix.translate(100, 200);
	//object->matrix.rotate(30);
	//object->rotation += 30;
	object->mass = 10;

	object->ID = 0;
	object->CalculateAABB();
	object->aabb->object = object;
	map.nsquared.Add(object->aabb);

	map.Add(object);


	Object *object2 = new Object("quad", "block");

	object2->matrix.translate(500, 400);
	//object2->matrix.rotate(25);
	//object2->rotation += 25;
	object2->ID = 1;
	object2->mass = 10;

	object2->CalculateAABB();
	object2->aabb->object = object2;

	map.nsquared.Add(object2->aabb);
	map.Add(object2);


	Object *object3 = new Object("quad", "wall");

	object3->ID = 2;
	object3->mass = 100000000;

	sf::Vector2f a(27, 27);
	object3->matrix.scale(a);

	sf::Vector2f b(0, 25);
	object3->matrix.translate(b);

	object3->CalculateAABB();
	object3->aabb->object = object3;

	map.nsquared.Add(object3->aabb);

	map.Add(object3);


	Object *object4 = new Object("quad", "wall");
	object4->ID = 3;
	object4->mass = 10000000;
	sf::Vector2f c(1, 13);
	object4->matrix.scale(c);

	object4->CalculateAABB();
	object4->aabb->object = object4;

	map.nsquared.Add(object4->aabb);

	map.Add(object4);

	Object *object5 = new Object("quad", "wall");
	object5->ID = 4;
	object5->mass = 10000000;
	sf::Vector2f d(1, 13);
	object5->matrix.translate(1250, 0);
	object5->matrix.scale(d);

	object5->CalculateAABB();
	object5->aabb->object = object5;

	map.nsquared.Add(object5->aabb);

	map.Add(object5);

	Object *object6 = new Object("quad", "wall");
	object6->ID = 5;
	object6->mass = 10000000;
	sf::Vector2f e(23, 1);
	object6->matrix.translate(75, 50);
	object6->matrix.scale(e);

	object6->CalculateAABB();
	object6->aabb->object = object6;

	map.nsquared.Add(object6->aabb);

	map.Add(object6);

	noobjects = noobjects + 6;



	//Gameloop
	while (gameState != Game::Exiting)
	{

		Game::GameLoop();

	}

	mainWindow.close();
}

void Game::GameLoop()
{

	switch (gameState)
	{

	case Playing:
	{
		while (gameState == Playing)
		{

			while (mainWindow.pollEvent(currentEvent))
			{
				if (currentEvent.type == sf::Event::Closed)
				{
					gameState = Game::Exiting;
				}

				if (currentEvent.type == sf::Event::KeyPressed)
				{
					if (currentEvent.key.code == sf::Keyboard::A)
					{
						map.Get(1)->velocity.x = map.Get(1)->velocity.x - 10;
					}
					if (currentEvent.key.code == sf::Keyboard::D)
					{
						map.Get(1)->velocity.x = map.Get(1)->velocity.x + 10;
					}
					if (currentEvent.key.code == sf::Keyboard::W)
					{
						map.Get(1)->velocity.y = map.Get(1)->velocity.y - 10;
					}
					if (currentEvent.key.code == sf::Keyboard::S)
					{
						map.Get(1)->velocity.y = map.Get(1)->velocity.y + 10;
					}
					if (currentEvent.key.code == sf::Keyboard::Q)
					{
						Object *object = new Object("quad", "block");

						object->matrix.translate(500, 400);
						//object2->matrix.rotate(45);
						//object2->rotation += 45;
						object->ID = noobjects;
						object->mass = 10;

						object->CalculateAABB();
						object->aabb->object = object;

						map.nsquared.Add(object->aabb);

						map.Add(object);
					}
					if (currentEvent.key.code == sf::Keyboard::P)
					{
						Object *object = new Object("przemek", "block");

						object->matrix.translate(500, 400);
						//object->matrix.rotate(30);
						//object->rotation += 30;
						object->mass = 100;

						object->ID = noobjects;
						object->CalculateAABB();
						object->aabb->object = object;
						map.nsquared.Add(object->aabb);

						map.Add(object);
					}
					if (currentEvent.key.code == sf::Keyboard::T)
					{
						Object *object = new Object("triangle", "block");

						object->matrix.translate(500, 400);
						//object->matrix.rotate(30);
						//object->rotation += 30;
						object->mass = 100;

						object->ID = noobjects;
						object->CalculateAABB();
						object->aabb->object = object;
						map.nsquared.Add(object->aabb);

						map.Add(object);
					}

				}

			}

			mainWindow.clear(sf::Color(0, 0, 0));

			map.UpdateAll();

			map.Collisions();


			map.DrawAll(mainWindow);

			Handle_FPS();

			mainWindow.display();  //Display the screen

		}

		break;
	}

	}
}

void Game::Handle_FPS()
{
	nframes++;
	fpscountertimer += elapsedTime;
	fpsavg += (1 / elapsedTime);

	if (fpscountertimer >= 1)
	{
		int a = (fpsavg / nframes);
		fpsText.setString(std::to_string(a));
		fpscountertimer = 0;
		fpsavg = 0;
		nframes = 0;
	}

	mainWindow.draw(fpsText);

	elapsedTime = fps.restart().asSeconds();

}

ResourceManager Game::resManager;
Map Game::map;
int Game::nframes;
float Game::fpsavg;
float Game::fpscountertimer;
sf::Event Game::currentEvent;
sf::Font Game::font;
sf::Text Game::fpsText;
float Game::elapsedTime;
sf::Clock Game::fps;
Game::GameState Game::gameState = Playing;
sf::RenderWindow Game::mainWindow;
sf::View Game::view;
unsigned int Game::noobjects;