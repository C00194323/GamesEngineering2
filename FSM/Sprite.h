#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Animation.h"

class Sprite
{
public:

	Sprite(SDL_Window*);
	~Sprite();
	void IdleAnimation();
	void JumpingAnimation();
	void ClimbingAnimation();
	void Render();
private:
	SDL_Renderer * render;
	SDL_Texture * Texture;
	SDL_Rect SpriteRect;
	SDL_Rect frameRect;




};