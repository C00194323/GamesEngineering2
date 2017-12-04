#pragma once

#include "GameObject.h"
#include "BasicTypes.h"
#include "EventListener.h"
#include <string>
#include "Renderer.h"

#include "SDL_image.h"


// ------------------------------------------------------------------ 
//
// PLATFORM : ALL
// PRODUCT : RWM_1718_P1
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------ 
// PURPOSE : Creates a respawn region and once the player passes through the region 
// if the player dies thats where they will start the level from.  

class RespawnBox : public GameObject, public EventListener
{
private:
	Rect m_rectangle;
	Point2D m_respawnPoint;

	std::string m_imageName;
	SDL_Texture* m_image;

	double m_degrees;

	bool m_colliding;

public:
	RespawnBox(Rect r, Renderer &renderer);
	RespawnBox();
	~RespawnBox();

	void Render(Renderer & r);

	void Update(unsigned int deltaTime);

	void CheckBounds(int width, int height);

	void setColliding(bool colliding);

	void onEvent(EventListener::Event e);

	Rect getRect();

	GameObjectType type;
};