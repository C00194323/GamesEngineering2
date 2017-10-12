#pragma once
#include "Animation.h"
#include <iostream>

class State {
public: 
	virtual void idle(Animation* a)
	{}
	virtual void jumping(Animation* a)
	{}
	virtual void climbing(Animation*a)
	{}
};

class Idle : public State
{
public:
	Idle() {};
	~Idle() {};
	void jumping(Animation* a);
	void climbing(Animation* a);
	void idle(Animation* a);

};

class Jumping : public State
{
public:
	Jumping() {};
	~Jumping() {};
	void idle(Animation* a);
};

class Climbing : public State
{
public:
	Climbing() {};
	~Climbing() {};
	void idle(Animation* a)
	{
		std::cout << "Going from Climbing to Idling" << std::endl;
		a->setCurrent(new Idle);
		delete this;
	}

};