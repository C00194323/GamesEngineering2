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
// PURPOSE : Draws Rectangle Objects to represent platforms


class Platform : public GameObject
{
private:
	Rect m_rectangle;
	Colour m_colour;

public:
	Platform();
	~Platform();
	Platform(Point2D pos, float worldUnit);
	Platform(Rect r);

	void Render(Renderer & r);



	void Update(unsigned int deltaTime);

	void CheckBounds(int width, int height);

	Rect getRect();

	GameObjectType type;

	void setColliding(bool colliding);
};
