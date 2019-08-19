#pragma once
#include "CGameObject.h"
class Numeric :
	public CGameObject
{
	virtual void Start();
	virtual void Update(float deltaTime);
};

