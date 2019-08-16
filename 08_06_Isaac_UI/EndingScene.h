#pragma once
#include "Scene.h"
class EndingScene :
	public Scene
{
public:
	EndingScene();
	~EndingScene();

	virtual int Start();
	virtual int Update(float deltaTime);
};

