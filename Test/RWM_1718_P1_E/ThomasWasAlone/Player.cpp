#include "stdafx.h"
#include <iostream>
#include "Player.h"

Player::Player()
{
	
}

Player::~Player()
{
}

Player::Player(Rect r)
{
	rectangle = r;
	playerCentre = Point2D(rectangle.pos.x + (rectangle.size.w / 2), rectangle.pos.y + (rectangle.size.h / 2));
}

void Player::init() 
{
	velocity = 0;
	acc = 0.5f;
	speed = 0;
	maxSpeed = 10;
	friction = 2;
	slow = false;
	facing = 1;
	type = PLAYER;
	
	m_vel = Point2D(0, 0);
	m_falling = true;

	m_nextRectangleX = rectangle;
	m_nextRectangleY = rectangle;
}

void Player::Render(Renderer& r)
{
	r.drawRect(rectangle, colour);
}

void Player::Update(unsigned int deltaTime)
{
	// updates player position using the next rectangle position
	rectangle.pos.x = m_nextRectangleX.pos.x;
	rectangle.pos.y = m_nextRectangleY.pos.y;

	playerCentre = Point2D(rectangle.pos.x + (rectangle.size.w / 2), rectangle.pos.y + (rectangle.size.h / 2));
	
	// updates the x next position rectangles to match rectangle
	m_nextRectangleX = rectangle;
	m_nextRectangleY = rectangle;
	if (sinking)
	{
		//m_vel.x = 0;
		m_vel.y += gravity * deltaTime *0.0005f;; // converts delta time from milliseconds to seconds
		m_nextRectangleY.pos.y += m_vel.y;
	}
	else
	{
		if (m_vel.y != 0)
		{
			acc = 0.25f;
		}
		else
		{
			acc = 0.5f;
		}

		//if no key is pressed slow the player down
		if (slow)
		{
			speed *= 0.92;
			if (speed == 0)
				slow = false;
		}

		handleJump(deltaTime);


		m_nextRectangleX.pos.x += speed * deltaTime / 30;

		// player is falling due to gravity
		// converts delta time from milliseconds to seconds
		m_vel.y += gravity * deltaTime / 2000; 
		m_nextRectangleY.pos.y += m_vel.y;
	}
}

void Player::onEvent(EventListener::Event evt)
{
	switch (evt)
	{
		if (!sinking)
		{
	case EventListener::MOVERIGHT:
		slow = false;
		if (speed < maxSpeed) 
		{
			speed += acc;
			facing = 1;
			if (speed > maxSpeed)
				speed = maxSpeed;
		}
		break;
	case EventListener::MOVELEFT:
		slow = false;
		if (speed > -maxSpeed) 
		{
			speed -= acc;
			facing = -1;
			if (speed < -maxSpeed)
				speed = -maxSpeed;
		}
		break;
	case EventListener::NOTMOVINGRIGHT:
		slow = true;
		break;
	case EventListener::NOTMOVINGLEFT:
		slow = true;
		break;
	case EventListener::JUMPHELD:
		if (!held)
			held = true;
		break;
	case EventListener::JUMPRELEASED:
		held = false;
		released = true;
		break;
	default:
		break;
		}
	}


}


void Player::CheckBounds(int width, int height)
{
	if (m_nextRectangleX.pos.x > width - 20)
	{
		m_nextRectangleX.pos.x = width - 20;
		speed = 0;
	}

	else if (m_nextRectangleX.pos.x < 0)
	{
		m_nextRectangleX.pos.x = 0;
		speed = 0;
	}
}

void Player::handleJump(unsigned int deltaTime)
{
	if (held)//if space held
	{
		holdTime += deltaTime; //count how long space is held
	}
	else if (released) //when space is released, set up the jump
	{
		released = false;
		if (m_vel.y != 0)
		{
			onGround = false;
		}
		if (onGround)
		{
			if (holdTime >= 400)//ms
			{
				maxHeight = 10; //super jump
			}
			else
			{
				maxHeight = 7; //normal jump
			}
			holdTime = 0; //reset clock
			onGround = false;
			jump = true;
			jumpAccel = 15.f;
			yTarget = rectangle.pos.y - (maxHeight * 20.f);//apex location
		}
	}

	if (jump)
	{
		m_nextRectangleY.pos.y -= jumpAccel * deltaTime / 30; 
		if (rectangle.pos.y <= yTarget || topCollision)
		{//initiate gravity at the apex
			jumpAccel = 0;
			topCollision = false;
		}
		if (onGround) 
		{ //back on the ground, finished jumping. Must be updated when collision is in!!!!!
			jump = false;
			
		}
	}
}

void Player::setPos(Point2D newPos) 
{
	rectangle.pos = newPos;
	m_nextRectangleX.pos = newPos;
	m_nextRectangleY.pos = newPos;
}

void Player::CheckCollisions(GameObject* platform, unsigned int deltaTime)
{
	
	// checks for intersection between next x position of the player and the platforms
	if (m_nextRectangleX.pos.x < platform->getRect().pos.x + platform->getRect().size.w
		&& m_nextRectangleX.pos.x + m_nextRectangleX.size.w > platform->getRect().pos.x
		&& m_nextRectangleX.pos.y < platform->getRect().pos.y + platform->getRect().size.h
		&& m_nextRectangleX.pos.y + m_nextRectangleX.size.h > platform->getRect().pos.y)
	{
		// left collision
		if (m_nextRectangleX.pos.x < platform->getRect().pos.x + platform->getRect().size.w && m_nextRectangleX.pos.x > platform->getRect().pos.x)
		{
			if (!sinking)
			{
				speed = 0;
				m_nextRectangleX.pos.x = platform->getRect().pos.x + platform->getRect().size.w;
			}

			//std::cout << "left collision" << std::endl;
		}

		//right collision
		else if (m_nextRectangleX.pos.x + m_nextRectangleX.size.w > platform->getRect().pos.x&& m_nextRectangleX.pos.x + m_nextRectangleX.size.w < platform->getRect().pos.x + platform->getRect().size.w)
		{
			if (!sinking)
			{
				speed = 0;
				m_nextRectangleX.pos.x = platform->getRect().pos.x - m_nextRectangleX.size.w;
			}

			//std::cout << "right collision" << std::endl;
		}
	}

	// checks for intersection between next y position of the player and the platforms
	if (m_nextRectangleY.pos.x < platform->getRect().pos.x + platform->getRect().size.w
		&& m_nextRectangleY.pos.x + m_nextRectangleY.size.w > platform->getRect().pos.x
		&& m_nextRectangleY.pos.y < platform->getRect().pos.y + platform->getRect().size.h
		&& m_nextRectangleY.pos.y + m_nextRectangleY.size.h > platform->getRect().pos.y)
	{
		// bottom collision
		if (m_nextRectangleY.pos.y + m_nextRectangleY.size.h > platform->getRect().pos.y && m_nextRectangleY.pos.y + m_nextRectangleY.size.h < platform->getRect().pos.y + platform->getRect().size.h)
		{
			if (platform->type == GameObjectType::PLATFORM && !sinking)
			{
				m_vel.y = 0;
				m_nextRectangleY.pos.y = platform->getRect().pos.y - m_nextRectangleY.size.h;

				onGround = true;
			}
			else if(platform->type == GameObjectType::WATER)
			{
				sinking = true;
			}
		}
		

		// top collision
		else if (m_nextRectangleY.pos.y < platform->getRect().pos.y + platform->getRect().size.h && m_nextRectangleY.pos.y > platform->getRect().pos.y)
		{
			if (!sinking)
			{
				m_vel.y = 0;
				m_nextRectangleY.pos.y = platform->getRect().pos.y + platform->getRect().size.h;
				topCollision = true;
			}
		}
	}
}

bool Player::intersect(GameObject *object)
{
	if (playerCentre.x > object->getRect().pos.x
		&& playerCentre.x < object->getRect().pos.x + object->getRect().size.w
		&& playerCentre.y > object->getRect().pos.y
		&& playerCentre.y < object->getRect().pos.y + object->getRect().size.h)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Rect Player::getRect()
{
	return rectangle;
}

void Player::setColliding(bool colliding)
{

}
	
void Player::Restart()
{
	//velocity = 0;
	acc = 0.5f;
	speed = 0;

	slow = false;

	m_vel = Point2D(0, 0);
	m_falling = true;

	sinking = false;
	//rectangle.pos.x = 310;
	//rectangle.pos.y = 0;
	//
	//m_nextRectangleX = rectangle;
	//m_nextRectangleY = rectangle;
}
