#pragma once
#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "IGraphic.h"

class Graphics : public IGraphic
{
public:
	Graphics();
	~Graphics();
	void Draw();
};

#endif