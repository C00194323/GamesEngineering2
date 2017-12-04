#pragma once

#include "Renderer.h"
#include "math.h"
#include <string>

// ------------------------------------------------------------------ 
//
// PLATFORM : ALL
// PRODUCT : RWM_1718_P1
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------ 
// PURPOSE : Base class for use in almost all objects in use in the program,
// for ease of use in updating and rendering objects

class GameObject
{
public:
	GameObject() {};
	virtual ~GameObject() {};
	virtual void Render(Renderer& r)=0;
	virtual void Update(unsigned int deltaTime)=0;
	virtual void CheckBounds(int width, int height) = 0;
	virtual Rect getRect() = 0;

	virtual void setColliding(bool colliding) = 0;
	enum GameObjectType{PLAYER, PLATFORM, PORTAL, WATER, RESPAWNBOX};

	GameObjectType type;
};

