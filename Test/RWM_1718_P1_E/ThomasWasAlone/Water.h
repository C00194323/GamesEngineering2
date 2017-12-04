#pragma once

#include "GameObject.h"
#include "BasicTypes.h"
#include "EventListener.h"

// ------------------------------------------------------------------ 
//
// PLATFORM : ALL
// PRODUCT : RWM_1718_P1
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------ 
// PURPOSE : Creates a blue rectangle to represent the water and sets 
// a bool to check for collision between itself and the player.

class Water : public GameObject
{
public:
	Water();
	~Water();

	Water(Point2D pos, float worldUnit);
	Water(Rect r);

	void Render(Renderer & r);

	void Update(unsigned int deltaTime);

	Rect getRect();

	GameObjectType type;

	void CheckBounds(int w, int h);

	void setColliding(bool colliding);

private:
	Rect m_rectangle;
	Colour m_colour;



};

