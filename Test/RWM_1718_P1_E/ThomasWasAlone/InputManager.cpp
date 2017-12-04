#include "stdafx.h"
#include "InputManager.h"


InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::AddListener(EventListener::Event evt,EventListener *listener)
{
	//event not in map add it.
	if (listeners.find(evt) == listeners.end())
	{ 
		
		listeners[evt] = new std::vector<EventListener*>();
	}

	listeners[evt]->push_back(listener);

}

//Send the events to interested objects
void InputManager::Dispatch(EventListener::Event evt)
{
	if (listeners.find(evt) != listeners.end())
	{
		//go through all listeners for this event
		for (auto const &listener : *listeners[evt])
		{ 
			//Call on event for the listener
			listener->onEvent(evt);

			//add the event to a list of events this frame
			evts.push_back(evt); 
		}
	}
	
}


//Gnereate events
void InputManager::ProcessInput()
{
	evts.clear();
	const Uint8* currentKeys = SDL_GetKeyboardState(NULL);
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type) {
			/* Keyboard event */
			
			case SDL_KEYDOWN:

				if (states->currentState == gameStates::GAMEOVER)
				{
					if (states->transitioning == false)
					{
						if (currentKeys[SDL_SCANCODE_Q])
						{
							Dispatch(EventListener::Event::QUIT);
							states->transitioning = true;
							break;
						}
						else
						{
							states->transitioning = true;
							Dispatch(EventListener::Event::RESTART);
							break;
						}
					}

				}
				if (states->currentState == gameStates::START)
				{
					if (states->transitioning == false)
					{
						//a check to transition right to the gameover screen, for verification and testing
						if (currentKeys[SDL_SCANCODE_Q]&& currentKeys[SDL_SCANCODE_LSHIFT]&& currentKeys[SDL_SCANCODE_LCTRL])
						{
							states->transitioning = true;
							Dispatch(EventListener::Event::GAMEOVER);
							break;
						}
						states->transitioning = true;
						Dispatch(EventListener::Event::START);
						break;
					}


				}
				switch (e.key.keysym.sym)
				{

				case SDLK_SPACE:
					Dispatch(EventListener::Event::JUMPHELD);
					break;
				case SDLK_d:
					Dispatch(EventListener::Event::MOVERIGHT);
					break;
				case SDLK_a:
					Dispatch(EventListener::Event::MOVELEFT);
					break;
				case SDLK_l:
					Dispatch(EventListener::Event::RECORD);
					break;
				default:
					break;
				}
				break;
			case SDL_KEYUP:
				//this is to prevent inputs being held from one screen to another triggering another event too quickly
				if (states->transitioning == true)
				{
					states->transitioning = false;
				}
				switch (e.key.keysym.sym)
				{
				case SDLK_SPACE:
					Dispatch(EventListener::Event::JUMPRELEASED);
					break;
				case SDLK_d:
					Dispatch(EventListener::Event::NOTMOVINGRIGHT);
					break;
				case SDLK_a:
					Dispatch(EventListener::Event::NOTMOVINGLEFT);
					break;
				default:
					break;
				}

				break;

			
			/* SDL_QUIT event (window close) */

			case SDL_QUIT:
				Dispatch(EventListener::Event::QUIT);
				break;

			default:
				break;
			}
		
		
	
	}
	//check for exit
}
std::vector<EventListener::Event> InputManager::getEventsList()
{
	return evts;
}