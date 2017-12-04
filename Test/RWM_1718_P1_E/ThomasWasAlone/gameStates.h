#pragma once

// ------------------------------------------------------------------ 
//
// PLATFORM : ALL
// PRODUCT : RWM_1718_P1
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------ 
// PURPOSE : Stores a number of possible game states,
// the current game state and a boolean used 
// to check when a screen is changing

class gameStates
{
public:
	enum states
	{
		START,
		GAME,
		GAMEOVER
	};
	bool transitioning=false;
	int currentState;
};
