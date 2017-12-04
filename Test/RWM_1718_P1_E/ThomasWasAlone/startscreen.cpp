#include "stdafx.h"
#include "startscreen.h"


startscreen::startscreen()
{
	//default constructor, not used

}

startscreen::startscreen(Renderer & r)
{
	path = "start.png";
	img = loadSurface(r);
	loadFont(50,255,255,255);
	generateFontSurface(r, Point2D(0, 300), "press any key to start!");
	generateFontSurface(r, Point2D(0, 0), "Tomás was alone");
	loadFont(20, 255, 255, 255);
	generateFontSurface(r, Point2D(0, 100), "RWM 17-18 team E");
	generateFontSurface(r, Point2D(0, 200), "made by: Sean Kearns, Jack Scully,");
	generateFontSurface(r, Point2D(0, 230), "David Buckingham, Dale Sinnott, Dermot Mac Conville");
	generateFontSurface(r, Point2D(0, 260), "Supervised by: Daire oBroin, Martin Harrigan");

	path = "carlow.png";
	loadSurface(r,500, 400, 300, 155);
}


startscreen::~startscreen()
{
}

void startscreen::CheckBounds(int width, int height)
{

}

void startscreen::Render(Renderer & r)
{
	SDL_Rect* rect = new SDL_Rect{ 0,0,600,100 };
	r.drawImage(img);
	//	r.drawImage(textImg, rect);
	for (size_t i = 0; i < TextureVector.size(); i++)
	{
		r.drawImage(TextureVector[i].texture, TextureVector[i].rect);
	}
}

void startscreen::Update(unsigned int deltaTime)
{

}

void startscreen::onEvent(EventListener::Event)
{

}
//for loading only loading a texture and returning it
SDL_Texture * startscreen::loadSurface(Renderer & r)
{
	SDL_Texture* optimizedSurface = NULL;
	SDL_Texture* loadedSurface = IMG_LoadTexture(r.getRenderer(), path.c_str());

	optimizedSurface = loadedSurface;
	return optimizedSurface;
}
//loads a texture with specified dimensions and position
void startscreen::loadSurface(Renderer& r, int x, int y, int w, int h)
{
	TextureContainer textures;
	SDL_Rect* tempRect = new SDL_Rect{ x,y,w,h };
	SDL_Texture* loadedSurface = IMG_LoadTexture(r.getRenderer(), path.c_str());


	textures.texture = loadedSurface;
	textures.rect = tempRect;
	TextureVector.push_back(textures);
}
//loading a default font with colour and size
void startscreen::loadFont()
{
	textFont = TTF_OpenFont("AGENCYR.ttf", 50);
	textCol.a = 255;
	textCol.b = 199;
	textCol.g = 160;
	textCol.r = 255;
}
//loading a font with colour and size
void startscreen::loadFont(int fontSize, int r, int g, int b)
{
	textFont = TTF_OpenFont("AGENCYR.ttf", fontSize);
	textCol.a = 255;
	textCol.b = b;
	textCol.g = g;
	textCol.r = r;
}
//deprecated, for testing. turns font and text into a texture 
SDL_Texture * startscreen::generateFontSurface(Renderer & r)
{
	TextureContainer textures;
	std::string text = "this is a test, hello world";
	SDL_Texture* temp = NULL;
	SDL_Surface* tempSurf = NULL;
	tempSurf = TTF_RenderText_Solid(textFont, text.c_str(), textCol);

	temp = SDL_CreateTextureFromSurface(r.getRenderer(), tempSurf);
	textures.texture = temp;

	return temp;
}
//generates a texture with specified text
void startscreen::generateFontSurface(Renderer & r, Point2D pos, std::string textToWrite)
{
	TextureContainer textures;
	std::string text = textToWrite;
	SDL_Texture* temp = NULL;
	SDL_Surface* tempSurf = NULL;
	tempSurf = TTF_RenderText_Solid(textFont, text.c_str(), textCol);

	temp = SDL_CreateTextureFromSurface(r.getRenderer(), tempSurf);
	textures.texture = temp;
	SDL_Rect* rectangle = new SDL_Rect{ (int)pos.x,(int)pos.y,(int)tempSurf->w, (int)tempSurf->h };
	textures.rect = rectangle;
	TextureVector.push_back(textures);


}

Rect startscreen::getRect()
{
	//inherits from the abstract class
	return Rect();
}

void startscreen::setColliding(bool colliding)
{

}