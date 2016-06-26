
#pragma once
#include "stdafx.h"
#include "Game.h"

void Game::Start()
{
	mainWindow.create(sf::VideoMode(1280, 720, 32), "Physics");
	view.setCenter(1280 / 2, 720 / 2);
	view.setSize(1280, 720);
	mainWindow.setView(view);

	gameState = Playing;

	font.loadFromFile("fonts/consola.ttf");

	fpsText.setColor(sf::Color::Red);
	fpsText.setPosition(10, 10);
	fpsText.setFont(font);

	noobjects = 0;
	fpsavg = 0;

	resManager.DefineTriangle();

	Object object("triangle");
	object.ptr = resManager.Get("triangle");

	map.Add(object);

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

			}

			mainWindow.clear(sf::Color(0, 0, 0));

			map.UpdateAll();

			SpatialGrid grid;
			grid.Update();

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