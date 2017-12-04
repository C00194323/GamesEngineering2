#include "stdafx.h"
#include <iostream>
#include "SDL_image.h"
using namespace std;
#define SDL_MAIN_HANDLED

#ifdef __APPLE__
    #include "SDL2/SDL.h"
#elif defined(_WIN64) || defined(_WIN32)
    #include "SDL.h"
#endif

#include "Renderer.h"




Renderer::Renderer():sdl_renderer(NULL)
{
	
}

bool Renderer::init(const Size2D& winSize,const char* title)
{

	int e=SDL_Init(SDL_INIT_EVERYTHING);              // Initialize SDL2
	IMG_Init(IMG_INIT_PNG);
	windowSize = winSize;
	if (e != 0) {
		// problem with SDL?...
		cout << "Could not init SDL: " << SDL_GetError() << std::endl;
		return false;
	}


	// Create an application window with the following settings:
	window = SDL_CreateWindow(
		title,                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		(int)winSize.w,                              // width, in pixels
		(int)winSize.h,                               // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
	);

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		cout << "Could not create window: " << SDL_GetError() << std::endl;
		return false;
	}

	//Initialize PNG loading 
	int imgFlags = IMG_INIT_PNG; 
	if( !( IMG_Init( imgFlags ) & imgFlags ) ) 
	{ 
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		//success = false; 
	}
	//initialize ttf loading
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		
	}
	sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (sdl_renderer == NULL) {
		// In the case that the renderer could not be made...
		cout << "Could not create renderer: " << SDL_GetError() << std::endl;
		return false;
	}
	
	return true;
}

//draw a rect in pixel coordinates
void Renderer::drawRect(const Rect& r, const Colour& c) 
{
	SDL_SetRenderDrawBlendMode(sdl_renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(sdl_renderer, c.r, c.g, c.b, c.a);
	SDL_Rect sr;
	sr.h = (int)r.size.h;
	sr.w = (int)r.size.w;
	sr.x = (int)r.pos.x;
	sr.y = (int)r.pos.y;
	SDL_RenderFillRect(sdl_renderer, &sr);

}
void Renderer::drawPortal(const Rect &r, const Colour &c)
{
	SDL_SetRenderDrawColor(sdl_renderer, c.r, c.g, c.b, c.a);
	SDL_Rect sr;
	sr.h = (int)r.size.h;
	sr.w = (int)r.size.w;
	sr.x = (int)r.pos.x;
	sr.y = (int)r.pos.y;
	SDL_RenderDrawRect(sdl_renderer, &sr);
}
//basic image drawing, draws to the whole screen, stretching it.
void Renderer::drawImage(SDL_Texture* surface)
{
	SDL_RenderCopy(sdl_renderer, surface, NULL, NULL);
}
//draws a texture with a specified position and dimensions
void Renderer::drawImage(SDL_Texture * surface, SDL_Rect* textureRect)
{
	SDL_RenderCopy(sdl_renderer, surface, NULL, textureRect);
}
//draws a texture with a specified position, dimension and allows for rotation
void Renderer::drawRotateableImage(SDL_Texture * surface, double rotation, SDL_Point* origin, bool flip)
{
	SDL_RenderCopyEx(sdl_renderer, surface, NULL, NULL, rotation, origin, SDL_RendererFlip::SDL_FLIP_NONE);	
}

void Renderer::drawRotateableImage(SDL_Texture * surface, SDL_Rect* rect, double rotation, SDL_Point* origin, bool flip)
{
	SDL_RenderCopyEx(sdl_renderer, surface, NULL, rect, rotation, origin, SDL_RendererFlip::SDL_FLIP_NONE);
}
//for getting the window, which is needed for generating text
SDL_Window * Renderer::getWindow()
{
	return window;
}

//draw a rectin world coordinates
void Renderer::drawWorldRect(const Rect &r, const Colour &c)
{
	drawRect(r,c);
}

void Renderer::drawPortalRect(const Rect &r, const Colour &c)
{
	drawPortal(r, c);
}

void Renderer::present() { //swap buffers
	SDL_RenderPresent(sdl_renderer);
}

void Renderer::clear(const Colour& col)
{
	SDL_SetRenderDrawBlendMode(sdl_renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(sdl_renderer, col.r, col.g, col.b, col.a);
	SDL_RenderClear(sdl_renderer);

}
Point2D Renderer::worldToScreen(const Point2D &p)
{
	float vpTop = viewportBottomLeft.y + viewportSize.h;
	float x = (p.x - viewportBottomLeft.x)* windowSize.w / viewportSize.w;
	float y = (vpTop- p.y)* windowSize.h / viewportSize.h;
	
	return Point2D(x,y);
}
Rect Renderer::worldToScreen(const Rect &r)
{
	Point2D p = worldToScreen(r.pos);
	float sw = r.size.w*(windowSize.w / viewportSize.w);
	float sh = -r.size.h*(windowSize.h / viewportSize.h);

	return Rect(p,Size2D(sw,sh));
}


SDL_Renderer* Renderer::getRenderer()
{
	return sdl_renderer;
}

void Renderer::setViewPort(const Rect &r)
{
	viewportBottomLeft = r.pos;
	viewportSize=r.size;
}


/**Destroys SDL_Window and SDL_Renderer*/
void Renderer::destroy() 
{
	SDL_DestroyRenderer(sdl_renderer);
	SDL_DestroyWindow(window);
	
}

Renderer::~Renderer()
{
}
