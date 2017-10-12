#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Animation.h"
#include "Sprite.h"
#include <iostream>
#include <thread>
#include <chrono>


int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	SDL_Window* window = SDL_CreateWindow("Hello Sean", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_SHOWN);
	SDL_Texture *image = nullptr;
	//SDL_Renderer *renderPlayer = nullptr;




	

	//renderPlayer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	Sprite player(window);

	bool isRunning = true;
	Animation fsm;
	int i = 0;


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

		player.Render();

		if (i == 0)
		{
			fsm.jumping();
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			i = 1;
		}
		else if (i == 1)
		{
			fsm.climbing();
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			i = 2;
		}
		else if (i == 2)
		{
			fsm.idle();
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			i = 0;
		}
	
	}
	SDL_Quit();
	return 0;
}