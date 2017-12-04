#pragma once

#include "GameObject.h"
#include "BasicTypes.h"
#include "EventListener.h"
#include "Player.h"
#include "Level.h"

// ------------------------------------------------------------------ 
//
// PLATFORM : ALL
// PRODUCT : RWM_1718_P1
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------ 
// PURPOSE : Draws Rectangle object to represent the Portal.


class Portal : public GameObject, public EventListener
{
public:
	Portal();
	Portal(Rect port, Colour);
	~Portal();

	Colour Portalcolour;
	Rect m_portalRect;


	float centre;
	

	void Render(Renderer & r);

	Rect Portal::getRect();


	void Update(unsigned int deltaTime);

	void CheckBounds(int width, int height);

	void onEvent(EventListener::Event);

	void setColliding(bool colliding);
};