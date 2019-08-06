#pragma once
#include "CGameObject.h"
class HPBar :
	public CGameObject
{
public:
	virtual void Start();
	virtual void Update(float deltaTime);

	float ratio;
	CGameObject * Emptybar;
};

