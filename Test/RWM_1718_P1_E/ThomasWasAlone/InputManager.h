#pragma once

#define SDL_MAIN_HANDLED
#ifdef __APPLE__
#include "SDL2/SDL.h"
#elif defined(_WIN64) || defined(_WIN32)
#include "SDL.h"
#endif


#include<map>
#include<vector>
#include "gameStates.h"
#include "EventListener.h"


// ------------------------------------------------------------------ 
//
// PLATFORM : ALL
// PRODUCT : RWM_1718_P1
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------ 
// PURPOSE : Provides key input handling for the game
// necessary for events and gameplay.

class InputManager
{
	//dictionary holding a list of litener objs for each event type
	std::map<EventListener::Event,
		std::vector<EventListener*>* //pointer to vec of eventlisteners
	> listeners;

public:
	InputManager();
	
	~InputManager();

	void AddListener(EventListener::Event, EventListener*);
	void Dispatch(EventListener::Event);
	gameStates* states;
	void ProcessInput();

	///Logging
	std::vector<EventListener::Event> evts;
	std::vector<EventListener::Event> getEventsList();
};

