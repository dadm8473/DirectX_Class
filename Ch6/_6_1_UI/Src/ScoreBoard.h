#pragma once
#include "CGameObject.h"
class ScoreBoard :
	public CGameObject
{
	virtual void Start();
	virtual void Update(float deltaTime);

	Numeric* Score[5];
};

