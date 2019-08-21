#pragma once
#include "CGameObject.h"
class CPlayerCheck :
	public CGameObject
{
public:
	bool bCheck = false;
	CGameObject * player = NULL;

	virtual void Start();
	virtual void Update(float deltaTime);

	virtual void OnCollision(CGameObject* CollisionObject);
};

