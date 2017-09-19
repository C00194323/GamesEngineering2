#pragma once
#ifndef GRAPHIC_PROXY_H
#define GRAPHIC_PROXY_H

#include "Graphics.h"
#include "IGraphic.h"

class GraphicProxy : public IGraphic
{
public:
	GraphicProxy();
	~GraphicProxy();
	void Draw();

private:
	Graphics* graphic;
	Graphics* getInstance(void);
};

#endif