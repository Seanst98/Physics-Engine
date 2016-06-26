#pragma once
#include "stdafx.h"
#include "Map.h"
#include "ResourceManager.h"
#include "SpatialGrid.h"

#define ET Game::GetET()  //Creating a macro for returning the elapsed time 

class Game
{

public:
	static void Start();
	static float GetET() { return elapsedTime; }
	static unsigned int noobjects;
	static sf::RenderWindow mainWindow;
	static Map map;
	static ResourceManager resManager;

	enum GameState {
		Playing, Exiting
	};

	static GameState gameState;

private:
	static void GameLoop();
	static void Handle_FPS();

	static int nframes;
	static float fpsavg;
	static float fpscountertimer;
	static sf::Font font;
	static sf::Text fpsText;
	static sf::Clock fps;
	static float elapsedTime;
	static sf::Event currentEvent;
	static sf::View view;
};
