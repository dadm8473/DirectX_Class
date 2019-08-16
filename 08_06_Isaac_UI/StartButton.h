#pragma once
#include "CGameObject.h"
class StartButton :
	public CGameObject
{
public:
	StartButton();
	~StartButton();

	virtual void Start();
	virtual void OnCollision(CGameObject* CollisionObject);
};

