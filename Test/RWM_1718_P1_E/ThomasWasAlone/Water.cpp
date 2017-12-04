#include "stdafx.h"
#include "Water.h"

Water::Water()
{
}

Water::~Water()
{
}


Water::Water(Point2D pos, float worldUnit)
{
	m_rectangle = Rect(pos.x, pos.y, worldUnit, worldUnit);
	m_colour = Colour(0, 0, 255, 128);
}

Water::Water(Rect r)
{
	m_rectangle = r;
	m_colour = Colour(0, 0, 255, 128);
}

void Water::Render(Renderer& r)
{
	r.drawWorldRect(m_rectangle, m_colour);
}

void Water::Update(unsigned int deltaTime)
{

}

void Water::CheckBounds(int w, int h)
{

}

Rect Water::getRect()
{
	return m_rectangle;
}

void Water::setColliding(bool colliding)
{

}