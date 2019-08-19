#pragma once
#include "Scene.h"
class TitleScene :
	public Scene
{
public:
	TitleScene();
	~TitleScene();

	virtual int Start();
	virtual int Update(float deltaTime);
	virtual int Render();
};

