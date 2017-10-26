#pragma once
#include "Entity.h"
#include <iostream>
class AI_System
{
	std::vector<Entity> entities;
public:
	void addEntity(Entity e){}
	void update()
	{
		std::cout << "Health Component Updating" << std::endl;

	}
};