#include "stdafx.h"

#include "ScreenFader.h"

Fade::Fade()
{

}

Fade::~Fade()
{

}

Fade::Fade(Rect r)
{
	rectangle = r;
}

void Fade::Render(Renderer& r)
{
	r.drawWorldRect(rectangle, colour);
}

void Fade::Update(unsigned int deltaTime)
{
	if (fadingOut)
	{
		FadeOut();
	}

	 if (fadingIn)
	{
		FadeIn();
	}
}

void Fade::CheckFade(Player* player)
{
	if (player->sinking)
	{
		fadingIn = true;
	}

	if (restart)
	{
		restart = false;
		player->Restart();
	}

}

void Fade::CheckBounds(int width, int height)
{
}

void Fade::onEvent(EventListener::Event evt)
{
}

void Fade::FadeOut()
{
	colour.a-=2;
	if (colour.a <= 0)
	{
		colour.a = 0;
		fadingOut = false;
	}
}

void Fade::FadeIn()
{
	colour.a+=2;

	if (colour.a >= 255)
	{
		colour.a = 255;
		fadingIn = false;
		fadingOut = true;
		restart = true;
	}
}

Rect Fade::getRect()
{
	return rectangle;
}

void Fade::setColliding(bool colliding)
{

}