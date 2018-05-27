#pragma once
#include "stdafx.h"
#include "Game.h"
#include "GJK.h"
#include "EPA.h"
#include "Contact.h"

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

	Object *object = new Object("quad");

	object->matrix.translate(500, 500);

	object->ID = 0;

	map.Add(object);

	Object *object2 = new Object("przemek");

	object2->ID = 1;

	map.Add(object2);


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
						map.Get(1)->matrix.translate(-10,0);
					}
					if (currentEvent.key.code == sf::Keyboard::D)
					{
						map.Get(1)->matrix.translate(10, 0);
					}
					if (currentEvent.key.code == sf::Keyboard::W)
					{
						map.Get(1)->matrix.translate(0, -10);
					}
					if (currentEvent.key.code == sf::Keyboard::S)
					{
						map.Get(1)->matrix.translate(0, 10);
					}
				}

			}

			mainWindow.clear(sf::Color(0, 0, 0));

			map.UpdateAll();

			SpatialGrid grid;
			grid.Update();

			GJK gjk;

			if (gjk.Check(map.Objects[0], map.Objects[1]))
			{
				EPA epa;
				epa.Update(map.Objects[0], map.Objects[1], &gjk.simplex);
				
				Contact contacts;
				contacts.getPoints(map.Objects[0], map.Objects[1], epa.normal, epa.depth);

				Resolution resolution;
				resolution.Update(map.Objects[0], map.Objects[1], contacts.clippedpoints);
			}



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