#pragma once
#include "Scene.h"
class InGameScene :
	public Scene
{
public:

	InGameScene();
	~InGameScene();

	virtual int Start();

	virtual int Update(float deltaTime);

	virtual int Render();
};

