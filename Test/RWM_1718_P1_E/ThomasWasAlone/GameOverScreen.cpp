#include "stdafx.h"
#include "GameOverScreen.h"



GameOverScreen::GameOverScreen()
{
}

GameOverScreen::GameOverScreen(Renderer & r)
{
	path = "gameover.png";
	img=loadSurface(r);
	loadFont();
	generateFontSurface(r,Point2D(0,0),"Game over!");
	generateFontSurface(r, Point2D(0, 40), "Thanks for playing");
	loadFont(40, 0, 0, 0);
	generateFontSurface(r, Point2D(0, 400), "press q to quit");
	generateFontSurface(r, Point2D(0, 450), "press any other key to restart");
	path = "carlow.png";
	loadSurface(r, 500, 400, 300, 155);
	
}

void GameOverScreen::CheckBounds(int width, int height)
{
	//solely because of inheritance
}

void GameOverScreen::Render(Renderer & r)
{
	SDL_Rect* rect = new SDL_Rect{ 0,0,600,100 };
	r.drawImage(img);
	for (size_t i = 0; i < TextureVector.size(); i++)
	{
		r.drawImage(TextureVector[i].texture, TextureVector[i].rect);
	}
}

void GameOverScreen::Update(unsigned int deltaTime)
{
}

void GameOverScreen::onEvent(EventListener::Event)
{
}

GameOverScreen::~GameOverScreen()
{
}

//for loading only loading a texture and returning it
SDL_Texture * GameOverScreen::loadSurface(Renderer& r)
{

	SDL_Texture* optimizedSurface = NULL;
	SDL_Texture* loadedSurface = IMG_LoadTexture(r.getRenderer(), path.c_str());

	optimizedSurface = loadedSurface;
	return optimizedSurface;
}

//loading a default font with colour and size
void GameOverScreen::loadFont()
{
	textFont = TTF_OpenFont("AGENCYR.ttf", 50);
	textCol.a = 255;
	textCol.b = 93;
	textCol.g = 157;
	textCol.r = 191;
}

//loading a font with colour and size
void GameOverScreen::loadFont(int fontSize, int r, int g, int b)
{
	textFont = TTF_OpenFont("AGENCYR.ttf", fontSize);
	textCol.a = 255;
	textCol.b = b;
	textCol.g = g;
	textCol.r = r;
}

//deprecated, for testing. turns font and text into a texture 
SDL_Texture * GameOverScreen::generateFontSurface(Renderer& r)
{
	TextureContainer textures;
	std::string text = "this is a test, hello world";
	SDL_Texture* temp=NULL;
	SDL_Surface* tempSurf = NULL;
	tempSurf = TTF_RenderText_Solid(textFont, text.c_str(), textCol);
	
	temp = SDL_CreateTextureFromSurface(r.getRenderer(), tempSurf);
	textures.texture = temp;

	return temp;
}

//loads a texture with specified dimensions and position
void GameOverScreen::loadSurface(Renderer & r, int x, int y, int w, int h)
{
	TextureContainer textures;
	SDL_Rect* tempRect = new SDL_Rect{ x,y,w,h };
	SDL_Texture* loadedSurface = IMG_LoadTexture(r.getRenderer(), path.c_str());


	textures.texture = loadedSurface;
	textures.rect = tempRect;
	TextureVector.push_back(textures);
}

//generates a texture with specified text
void GameOverScreen::generateFontSurface(Renderer& r, Point2D pos, std::string textToWrite)
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


Rect GameOverScreen::getRect()
{
	return Rect(0, 0, 0, 0);
}

void GameOverScreen::setColliding(bool colliding)
{

}
