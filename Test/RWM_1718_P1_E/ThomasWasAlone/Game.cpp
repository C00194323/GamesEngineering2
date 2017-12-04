#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
using namespace std;



#include "LTimer.h"
#include "Game.h"
#include "Player.h"
#include "Portal.h"
#include "Level.h"
#include "GameOverScreen.h"

int width = 800;
int height = 600;
const int SCREEN_FPS = 100;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

struct logging {
	unsigned int time;
	float x, y;
	std::vector<EventListener::Event> events;
};

std::vector<logging> logCollection;
Game::Game()
{
	pause = false;
	quit = false;
	//setting the current state to start
	//this will let the game open with the starting screen
	gamestate.currentState = gameStates::START;
	inputManager.states = &gamestate;
}


Game::~Game()
{
}


bool Game::init() 
{
	Size2D winSize(800, 600);

	//creates our renderer, which looks after drawing and the window
	renderer.init(winSize,"Simple SDL App");

	//instantiates the game over and start screens seperately, 
	//as they're not part of the standard game objects
	//renderer is passed to load in textures and fonts

	gameOverScreen = new GameOverScreen(renderer);
	startScreen = new startscreen(renderer);

	//set up the viewport
	//we want the vp centred on origin and 20 units wide
	float aspectRatio = winSize.w / winSize.h;
	float vpWidth = 800;
	float worldUnit = 20.0f;
	Size2D vpSize(vpWidth, vpWidth / aspectRatio);


	Rect vpRect(Point2D(0, 0), vpSize);




	//create some game objects
	level.init(worldUnit);

	level.setupLevel(gameObjects, renderer);
	player = new Player(Rect(310, 0, worldUnit, worldUnit * 2)); 
	player->init();
	player->setPos(level.spawnPoint);
	player->colour = Colour(240, 100, 10);


	fader = new Fade(Rect(0, 0, 800, 600));
	fader->colour = Colour(0, 0, 0, 0);

	lastTime = LTimer::gameTime();

	//want game loop to pause
	inputManager.AddListener(EventListener::Event::PAUSE, this);
	inputManager.AddListener(EventListener::Event::MOVERIGHT, player);
	inputManager.AddListener(EventListener::Event::MOVELEFT, player);
	inputManager.AddListener(EventListener::Event::NOTMOVINGRIGHT, player);
	inputManager.AddListener(EventListener::Event::NOTMOVINGLEFT, player);
	inputManager.AddListener(EventListener::Event::JUMPHELD, player);
	inputManager.AddListener(EventListener::Event::JUMPRELEASED, player);
	inputManager.AddListener(EventListener::Event::QUIT, this);
	inputManager.AddListener(EventListener::Event::RECORD, this);
	inputManager.AddListener(EventListener::Event::RESTART, this);
	inputManager.AddListener(EventListener::Event::START, this);
	inputManager.AddListener(EventListener::Event::GAMEOVER, this);

	changeLevel = false;

	return true;
}


void Game::destroy()
{
	//empty out the game object vector before quitting
	for (std::vector<GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); i++)
	{
		delete *i;

	}
	gameObjects.clear();
	delete player;
	renderer.destroy();
}

//** calls update on all game entities*/
void Game::update()
{
	//millis since game started
	unsigned int currentTime = LTimer::gameTime();

	//time since last update
	unsigned int deltaTime = currentTime - lastTime;

	logging frameLog;

	frameLog.time = currentTime;
	//call update on all game objects
	//edit: only updates the game objects when the current state is set to game
	//so objects don't update during the end or start screens
	if (gamestate.currentState == gameStates::GAME)
	{
		for (std::vector<GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); i++)
		{
			// checks collisions between player and platforms
			if ((*i)->type == GameObject::GameObjectType::PLATFORM || (*i)->type == GameObject::GameObjectType::WATER)
			{
				player->CheckCollisions(*i,deltaTime);
			}
			else if ((*i)->type == GameObject::GameObjectType::PORTAL)
			{
				if (player->intersect(*i) == true)
				{
					if (level.m_currentLevel < 5) 
					{	
						level.m_currentLevel++;
						level.SwitchLevel();
					}
					else
					{
						player->setPos(Point2D(0, 0));
						level.m_currentLevel = 1;
						gamestate.currentState = gameStates::GAMEOVER;
						level.SwitchLevel();
						changeLevel = true;
						break;
					}
					changeLevel = true;
				}
			}
			else if ((*i)->type == GameObject::GameObjectType::RESPAWNBOX)
			{
				(*i)->Update(deltaTime);

				if (player->intersect(*i) == true)
				{
					level.spawnPoint = Point2D((*i)->getRect().pos.x + ((*i)->getRect().size.w) / 2,
						(*i)->getRect().pos.y + ((*i)->getRect().size.h / 2));
					(*i)->setColliding(true);
				}
				else
				{
					(*i)->setColliding(false);
				}
			}
		}
		fader->CheckFade(player);
		fader->Update(deltaTime);

		if (fader->restart == true)
		{
			player->setPos(level.spawnPoint);
		}

		player->Update(deltaTime);
		player->CheckBounds(800, 600);
	}
	frameLog.x = player->rectangle.pos.x;
	frameLog.y = player->rectangle.pos.y;
	frameLog.events = inputManager.getEventsList();
	if (recordLogs)
	{
		logCollection.push_back(frameLog);
	}
	//save the curent time for next frame
	lastTime = currentTime;
}

//** calls render on all game entities*/

void Game::render()
{
	// prepare for new frame
	renderer.clear(Colour(255,255,255,255));
	
	//render every object
	if (gamestate.currentState == gameStates::GAME)
	{
		player->Render(renderer);

		for (std::vector<GameObject*>::iterator i = gameObjects.begin(), e= gameObjects.end(); i != e; i++) 
		{
			(*i)->Render(renderer);
		}

		fader->Render(renderer);
	}
	else if (gamestate.currentState == gameStates::GAMEOVER)
	{
		gameOverScreen->Render(renderer);
	}
	if (gamestate.currentState == gameStates::START)
	{
		startScreen->Render(renderer);

	}

	// display the new frame (swap buffers)
	renderer.present();
}

// update and render game entities
void Game::loop()
{
	//to cap framerate
	LTimer capTimer;

	int frameNum = 0;

	//game loop
	while (!quit)
	{ 
	
		capTimer.start();

		inputManager.ProcessInput();

		if (changeLevel == true) 
		{
			level.setupLevel(gameObjects, renderer);
			player->setPos(level.spawnPoint);
			player->Restart();
			changeLevel = false;
		}

		//in pause mode don't bother updateing
		if (!pause)
		{
			update();
		}
		
		render();

		//time since start of frame
		int frameTicks = capTimer.getTicks();

		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			//Wait remaining time before going to next frame
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
	}
}

void Game::onEvent(EventListener::Event evt) 
{	
	switch (evt)
	{
	case EventListener::PAUSE:
		pause = !pause;
		break;
	case EventListener::QUIT:
		quit = true;
		break;
	case EventListener::RECORD:
		if (!recordLogs)
		{
			std::cout << "Recording logs... Press L to stop recording and write to file." << std::endl;
			recordLogs = true;
		}
		else
		{
			recordLogs = false;
			std::cout << "Recording ended... Writing to file..." << std::endl;
			std::string filename;
			auto t = std::time(nullptr);
			tm t_m;
			localtime_s(&t_m, &t);
			std::ostringstream oss;
			oss << std::put_time(&t_m, "%d-%m-%Y-%H-%M-%S");
			filename = "log-";
			filename += oss.str();
			filename += ".csv";
			ofstream logFile;
			logFile.open(filename.c_str());
			for (int i = 0; i < logCollection.size(); i++)
			{
				logFile << logCollection.at(i).time << "," << logCollection.at(i).x << "," << logCollection.at(i).y << ",";
				for (int j = 0; j < logCollection.at(i).events.size(); j++)
				{
					switch (logCollection.at(i).events.at(j))
					{
					case EventListener::PAUSE:
						logFile << "PAUSE" << ",";
						break;
					case EventListener::QUIT:
						logFile << "QUIT" << ",";
						break;
					case EventListener::MOVERIGHT:
						logFile << "MOVERIGHT" << ",";
						break;
					case EventListener::MOVELEFT:
						logFile << "MOVELEFT" << ",";
						break;
					case EventListener::NOTMOVINGRIGHT:
						logFile << "NOTMOVINGRIGHT" << ",";
						break;
					case EventListener::NOTMOVINGLEFT:
						logFile << "NOTMOVINGLEFT" << ",";
						break;
					case EventListener::RECORD:
						logFile << "RECORD" << ",";
						break;
					case EventListener::JUMPHELD:
						logFile << "JUMPHELD" << ",";
						break;
					case EventListener::JUMPRELEASED:
						logFile << "JUMPRELEASED" << ",";
						break;
					case EventListener::RESTART:
						logFile << "RESTART" << ",";
						break;
					case EventListener::START:
						logFile << "START" << ",";
						break;
					case EventListener::GAMEOVER:
						logFile << "GAMEOVER" << ",";
						break;
					default:
						break;
					}
				}
				logFile << "\n";
			}
			logFile.close();
			std::cout << "File written as: " << filename << std::endl;
			logCollection.clear();
		}
		break;
	default:
		break;
	}


	if (gamestate.currentState == gameStates::GAMEOVER)
	{
		if (evt == EventListener::Event::QUIT)
		{
			quit=true;
		}
		if (evt == EventListener::Event::RESTART)
		{
			gamestate.currentState = gameStates::START;
		}
	}
	if (gamestate.currentState == gameStates::START)
	{
		if (evt == EventListener::Event::START)
		{
			gamestate.currentState = gameStates::GAME;
		}
		if (evt == EventListener::Event::GAMEOVER)
		{
			gamestate.currentState = gameStates::GAMEOVER;
		}
	}
}
