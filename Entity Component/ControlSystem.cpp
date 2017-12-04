#include "ControlSystem.h"



ControlSystem::ControlSystem()
{
}


ControlSystem::~ControlSystem()
{
}

void ControlSystem::update()
{
	std::cout << "Control System" << std::endl;
	for (int i = 0; i < entities.size(); i++)
	{
		//entities.at(i).getComponents();
		entities.at(i).update();
	}
}