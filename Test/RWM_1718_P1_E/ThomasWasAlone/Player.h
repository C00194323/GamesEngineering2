#pragma once

#include "GameObject.h"
#include "BasicTypes.h"
#include "EventListener.h"
#include "Portal.h"
#include "Level.h"

// ------------------------------------------------------------------ 
//
// PLATFORM : ALL
// PRODUCT : RWM_1718_P1
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------ 
// PURPOSE : The core of the game logic and loops are preformed here 
// updating, drawing and some event management

class Player : public GameObject, public EventListener
{
private:
	float velocity;
	float acc;
	float speed;
	float maxSpeed;
	float friction;
	bool slow;
	int facing;

	Point2D m_vel;
	const float gravity = 10.0f;
	bool m_falling;
	

	Rect m_nextRectangleX; // next x position of where the player will be after x velocity is applied
	Rect m_nextRectangleY; // next y position of where the playre will be after y velocity is applied

public:
	Player(Rect r);
	Player();
	~Player();

	Point2D playerCentre;


	void init();
	void setPos(Point2D newPos);


	bool sinking = false;

	void Restart();
	///Jumping
	bool held = false;
	bool released = false;
	bool jump = false;
	bool onGround = true;
	float jumpAccel = 0;
	float yTarget;
	float maxHeight = 7.f;
	int holdTime = 0;
	bool topCollision = false;
	///
	Rect rectangle;
	Colour colour;

	void Render(Renderer & r);

	void Update(unsigned int deltaTime);
	bool intersect(GameObject *object);
	void CheckBounds(int width, int height);

	void handleJump(unsigned int deltaTime);

	void CheckCollisions(GameObject* platform, unsigned int deltaTime);


	void onEvent(EventListener::Event);

	GameObjectType type;

	Rect getRect();

	void setColliding(bool colliding);

	//void setVel(Point2D vel);
};
