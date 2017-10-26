#pragma once
#include "Component.h"
#include <iostream>
#include "BasicTypes.h"
#include <vector>

class PositionComponent : public Component
{
public:
	PositionComponent() : pos(200,200){}
	int getPosition()
	{
		return pos.x, pos.y; 
	}
	void setPosition(Point2D tempPos)
	{
		this->pos = tempPos;
	}
private:
	Point2D pos;
};