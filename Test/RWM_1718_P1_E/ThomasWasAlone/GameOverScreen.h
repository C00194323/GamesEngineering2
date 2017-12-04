#pragma once

#include "GameObject.h"
#include "EventListener.h"
#include "SDL2\include\SDL_image.h"
#include "stdafx.h"
#include <string>
#include <iostream>
#include "SDL2\include\SDL_ttf.h"
#include <vector>
#include "textureContainer.h"


// ------------------------------------------------------------------ 
//
// PLATFORM : ALL
// PRODUCT : RWM_1718_P1
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------ 
// PURPOSE : To show the player has completed the game, can quit or restart the game.


class GameOverScreen: public GameObject, public EventListener
{
public:
	GameOverScreen();
	GameOverScreen(Renderer& r);
	void CheckBounds(int width, int height);
	void Render(Renderer& r);
	void Update(unsigned int deltaTime);
	void onEvent(EventListener::Event);
	~GameOverScreen();
	SDL_Texture* loadSurface(Renderer& r);
	void loadFont();
	void loadFont(int fontSize, int r, int g, int b);
	SDL_Texture* generateFontSurface(Renderer& r);
	void loadSurface(Renderer& r, int x, int y, int h, int w);
	void generateFontSurface(Renderer& r, Point2D pos, std::string textToWrite);
	std::string path;

	Rect getRect();

	void setColliding(bool colliding);

private:
	std::vector<TextureContainer> TextureVector;
	SDL_Texture* img= NULL;
	SDL_Texture* textImg = NULL;
	TTF_Font* textFont = NULL;
	SDL_Color textCol = { 0,0,0 };

};
