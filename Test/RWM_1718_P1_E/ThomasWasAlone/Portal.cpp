#include "stdafx.h"
#include "Portal.h"
#include <iostream>

Portal::Portal()
{

}
Portal::Portal(Rect port, Colour portColour)
{
	m_portalRect = port;
	Portalcolour = portColour;
	
}
Portal::~Portal()
{}

void Portal::Render(Renderer& r)
{
	r.drawPortalRect(m_portalRect, Portalcolour);
}


Rect Portal::getRect()
{
	return m_portalRect;
}
void Portal::CheckBounds(int width, int height)
{

}

void Portal::Update(unsigned int deltaTime)
{

}

void Portal::onEvent(EventListener::Event evt)
{
	
}

void Portal::setColliding(bool colliding)
{

}