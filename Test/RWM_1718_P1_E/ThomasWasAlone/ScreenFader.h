#pragma once

#include "GameObject.h"
#include "BasicTypes.h"
#include "EventListener.h"
#include "Player.h"

// ------------------------------------------------------------------ 
//
// PLATFORM : ALL
// PRODUCT : RWM_1718_P1
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------ 
// PURPOSE : Contains a number of possible events, which are used to communicate 
// various changes or interactions between game objects

class Fade : public GameObject, public EventListener
{
public:
	Fade(Rect r);
	Fade();
	~Fade();

	void FadeIn();
	void FadeOut();

	Rect rectangle;
	Colour colour;
	bool fadingOut = false;
	bool fadingIn = false;
	void Render(Renderer & r);
	bool restart = false;
	void Update(unsigned int deltaTime);
	void CheckBounds(int width, int height);

	void CheckFade(Player* player);

	Rect getRect();

	void onEvent(EventListener::Event);

	void setColliding(bool colliding);
};


