#pragma once
#include "State.h"
#include "Animation.h"
#include <iostream>

void Idle::jumping(Animation* a)
{
	std::cout << "Jumping" << std::endl;
	a->setCurrent(new Idle());
	delete this;
}

void Idle::climbing(Animation* a)
{
	std::cout << "Climbing" << std::endl;
	a->setCurrent(new Idle());
	delete this;
}
void Idle::idle(Animation* a)
{
	std::cout << "idle" << std::endl;
	a->setCurrent(new Idle());
	delete this;
}