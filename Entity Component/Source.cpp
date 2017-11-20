#include <SDL.h>
#include <SDL_image.h>
#include "Entity.h"

//Components
#include "HealthComponent.h"
#include "PositionComponent.h"
#include "ControlComponent.h"

// Systems 
#include "RenderSystem.h"
#include "AI_System.h"
#include "ControlSystem.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{

	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	SDL_Window* window = SDL_CreateWindow("Hello Sean", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_SHOWN);
	SDL_Texture *image = nullptr;


	Entity player;
	Entity Alien;
	Entity Dog;
	Entity Cat;

	HealthComponent hc;
	PositionComponent pc;
	ControlComponent cc;
	

	
	Alien.addComponent(hc);
	Alien.addComponent(pc);

	Dog.addComponent(hc);
	Dog.addComponent(pc);

	Cat.addComponent(hc);
	Cat.addComponent(pc);
	
	player.addComponent(hc);
	player.addComponent(pc);
	player.addComponent(cc);



	AI_System ais;
	ControlSystem cs;
	RenderSystem rs;

	ais.addEntity(player);
	cs.addEntity(player);
	rs.addEntity(player);

	bool isRunning = true;


	while (isRunning)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
			}
			
		}
		ais.update();
		cs.update();
		rs.update();
	}
	SDL_Quit();
	return 0;
}