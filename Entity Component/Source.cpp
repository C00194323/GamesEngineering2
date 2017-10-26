#include <SDL.h>
#include <SDL_image.h>
#include "Entity.h"
#include "HealthComponent.h"
#include "AI_System.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{

	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	SDL_Window* window = SDL_CreateWindow("Hello Sean", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_SHOWN);
	SDL_Texture *image = nullptr;


	Entity player;
	HealthComponent hc;
	player.addComponent(hc);

	AI_System hs;
	hs.addEntity(player);

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
		hs.update();
	}
	SDL_Quit();
	return 0;
}