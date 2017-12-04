#pragma once

#include "SDL2\include\SDL_image.h"

// ------------------------------------------------------------------ 
//
// PLATFORM : ALL
// PRODUCT : RWM_1718_P1
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------ 
// PURPOSE : Sets up objects to hold a texture //

class TextureContainer
{
public:
	SDL_Texture* texture = NULL;
	SDL_Rect* rect = NULL;

private:

};