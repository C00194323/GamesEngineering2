#include <iostream>
#include "Graphics.h"
#include "GraphicProxy.h"

using namespace std;

GraphicProxy::GraphicProxy()
{
	this->graphic = 0;
}

GraphicProxy::~GraphicProxy()
{
	if (graphic)
		delete graphic;
}

Graphics* GraphicProxy::getInstance(void)
{
	if (!graphic)
		graphic = new Graphics();
	return graphic;
}

void GraphicProxy::Draw()
{
	getInstance()->Draw();
}