#pragma once

#include <iostream>
#include <vector>
#include "GameObject.h"
#include "Platform.h"
#include "Water.h"
#include "Player.h"
#include "Portal.h"
#include "RespawnBox.h"

// ------------------------------------------------------------------ 
//
// PLATFORM : ALL
// PRODUCT : RWM_1718_P1
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------ 
// PURPOSE : Sets Up the different levels and switches between them.


class Level 
{
public:
	Level();

	void init(float worldUnit);

	void setupLevel(std::vector<GameObject*> &objects, Renderer &renderer);
	void SwitchLevel();
	int m_currentLevel;
	Point2D spawnPoint;

private:
	static const int maxCol = 30;
	static const int maxRow = 39;

	// 2D arrays that hold each level layout
	static const int level1Layout[maxCol][maxRow]; 
	static const int level2Layout[maxCol][maxRow];
	static const int level3Layout[maxCol][maxRow];
	static const int level4Layout[maxCol][maxRow];
	static const int level5Layout[maxCol][maxRow];
	static const int level6Layout[maxCol][maxRow];

	//int m_currentLevel;
	int* m_pointerToLevel;

	float m_worldUnit;
};