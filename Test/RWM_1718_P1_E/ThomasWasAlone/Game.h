#pragma once

#include <vector>
#include "GameOverScreen.h"
#include "startscreen.h"
#include "Renderer.h"
#include "GameObject.h"
#include "InputManager.h"
#include "EventListener.h"
#include "ScreenFader.h"
#include "Player.h"
#include "Level.h"
#include "Portal.h"
#include "gameStates.h"


// ------------------------------------------------------------------ 
//
// PLATFORM : ALL
// PRODUCT : RWM_1718_P1
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------ 
// PURPOSE : The core of the game logic and loops are preformed here 
// updating, drawing and some event management

class Game:public EventListener
{
	InputManager inputManager;
	gameStates gamestate;
	Renderer renderer;
	startscreen* startScreen;
	std::vector<GameObject*> gameObjects;
	
	bool recordLogs = false;

	Fade* fader;
	Player* player;

	GameOverScreen* gameOverScreen;

	unsigned int lastTime;//time of last update;

	bool pause;
	bool quit;
	

public:
	Game();
	~Game();
	Portal* portal;
	bool init();
	void destroy();

	void update();
	void render();
	void loop();

	void onEvent(EventListener::Event);

	Level level;

	bool changeLevel;
};

