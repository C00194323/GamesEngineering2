#pragma once

// ------------------------------------------------------------------ 
//
// PLATFORM : ALL
// PRODUCT : RWM_1718_P1
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------ 
// PURPOSE : Contains a number of possible events, which are used to 
// communicate various changes or interactions between game objects

class EventListener
{
public:

	//list of possible events
	//add your own events here
	enum Event {
		PAUSE,
		QUIT,
		MOVERIGHT,
		MOVELEFT,
		NOTMOVINGRIGHT,
		NOTMOVINGLEFT,
		RECORD,
		JUMPHELD,
		JUMPRELEASED,
		RESTART,
		START,
		GAMEOVER
	};


	virtual void onEvent(Event)=0;
};

