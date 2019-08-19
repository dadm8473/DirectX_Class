#pragma once
#include "Scene.h"
class InGameScene :
	public Scene
{
public:

	float timer;
	float time;
	float sum;

public:

	InGameScene();
	~InGameScene();

	virtual int Start();

	virtual int Update(float deltaTime);

	virtual int Render();
};

