#pragma once
#include "CGameObject.h"
class Ending :
	public CGameObject
{
public:
	Ending();
	~Ending();

	virtual void Start();
	virtual void Update(float deltaTime);
};

