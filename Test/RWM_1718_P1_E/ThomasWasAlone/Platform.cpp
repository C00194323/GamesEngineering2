#include "stdafx.h"
#include "Platform.h"
#include "GameObject.h"

Platform::Platform()
{
	m_colour = Colour(0, 0, 0);
}

Platform::~Platform()
{

}

Platform::Platform(Point2D pos, float worldUnit) 
{
	m_rectangle = Rect(pos.x, pos.y, worldUnit, worldUnit);
	m_colour = Colour(0, 0, 0);
}

Platform::Platform(Rect r)
{
	m_rectangle = r;
	m_colour = Colour(0, 0, 0);
}

void Platform::Render(Renderer& r)
{
	r.drawRect(m_rectangle, m_colour);
}

void Platform::Update(unsigned int deltaTime) 
{

}

void Platform::CheckBounds(int w, int h)
{

}

Rect Platform::getRect()
{
	return m_rectangle;
}

void Platform::setColliding(bool colliding)
{

}