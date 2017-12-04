#pragma once
#include "Component.h"
#include <vector>
#include <iostream>
class Entity
{
	int id;
public:
	Entity() {};
	void addComponent(Component c)
	{
		components.push_back(c);
	}

	void removeComponents(Component c) {}

	std::vector<Component> getComponents() 
	{ 
		return components; 
	}
	void update()
	{
		for (int i = 0; i < components.size(); i++)
		{
			std::cout << "Component" << std::endl;
		}
	}

private:
	std::vector<Component> components;
	
};