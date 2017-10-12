#include "Sprite.h"
Sprite::Sprite(SDL_Window* window)
{
	render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	Texture = IMG_LoadTexture(render, "Jumping-SpriteSheet.png");
	SDL_SetRenderDrawColor(render, 0xFF, 0, 0, 0xFF);
	SDL_RenderClear(render);
	
	SpriteRect.x = 0;
	SpriteRect.y = 0;
	SpriteRect.w = 362;
	SpriteRect.h = 483;

	frameRect.x = 0;
	frameRect.y = 0;
	frameRect.w = 64;
	frameRect.h = 64;
	
}
Sprite::~Sprite()
{

}
void Sprite::JumpingAnimation()
{
	SpriteRect.x += 362;
	if (SpriteRect.y ==0 && SpriteRect.x >= 3620)
	{
		SpriteRect.x = 0;
		
	}
}
void Sprite::IdleAnimation()
{

}

void Sprite::Render()
{
	JumpingAnimation();
	SDL_RenderClear(render);
	SDL_RenderCopy(render, Texture, &SpriteRect, &frameRect);
	SDL_RenderPresent(render);
}

void Sprite::ClimbingAnimation()
{

}