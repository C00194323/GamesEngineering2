#include "stdafx.h"

#include "RespawnBox.h"

RespawnBox::RespawnBox()
{

}

RespawnBox::RespawnBox(Rect r, Renderer &renderer)
{
	m_rectangle = r;
	m_respawnPoint = Point2D((r.pos.x + r.size.w) / 2, (r.pos.y + r.size.h) / 2);

	m_imageName = "arrow.png";
	m_degrees = 0;

	m_image = IMG_LoadTexture(renderer.getRenderer(), m_imageName.c_str());

	m_colliding = false;
}

RespawnBox::~RespawnBox()
{

}

void RespawnBox::Render(Renderer &r)
{
	SDL_Rect* rectTop = new SDL_Rect;
	rectTop->x = m_rectangle.pos.x + 10;
	rectTop->y = m_rectangle.pos.y + 15;
	rectTop->w = 40;
	rectTop->h = 40;

	SDL_Point* rectTopOrigin = new SDL_Point;
	rectTopOrigin->x = rectTop->w / 2;
	rectTopOrigin->y = rectTop->h / 2;

	r.drawRotateableImage(m_image, rectTop, m_degrees, rectTopOrigin, false);

	delete rectTop;
	delete rectTopOrigin;

	SDL_Rect* rectMiddle = new SDL_Rect;
	rectMiddle->x = m_rectangle.pos.x + 10;
	rectMiddle->y = m_rectangle.pos.y + 80;
	rectMiddle->w = 40;
	rectMiddle->h = 40;

	SDL_Point* rectMiddleOrigin = new SDL_Point;
	rectMiddleOrigin->x = rectMiddle->w / 2;
	rectMiddleOrigin->y = rectMiddle->h / 2;

	r.drawRotateableImage(m_image, rectMiddle, m_degrees, rectMiddleOrigin, false);

	delete rectMiddle;
	delete rectMiddleOrigin;

	SDL_Rect* rectBottom = new SDL_Rect;
	rectBottom->x = m_rectangle.pos.x + 10;
	rectBottom->y = m_rectangle.pos.y + 145;
	rectBottom->w = 40;
	rectBottom->h = 40;

	SDL_Point* rectBottomOrigin = new SDL_Point;
	rectBottomOrigin->x = rectBottom->w / 2;
	rectBottomOrigin->y = rectBottom->h / 2;

	r.drawRotateableImage(m_image, rectBottom, m_degrees, rectBottomOrigin, false);

	delete rectBottom;
	delete rectBottomOrigin;
}

void RespawnBox::Update(unsigned int deltaTime)
{
	if (m_colliding == true) 
	{
		if (m_degrees > -45)
		{
			m_degrees -= 0.5f;
		}
	}
	else
	{
		if (m_degrees < 0)
		{
			m_degrees++;
		}
	}
}

void RespawnBox::CheckBounds(int w, int h)
{

}

void RespawnBox::onEvent(EventListener::Event)
{

}

Rect RespawnBox::getRect()
{
	return m_rectangle;
}

void RespawnBox::setColliding(bool colliding)
{
	if (m_colliding != colliding)
	{
		m_colliding = colliding;
	}
}