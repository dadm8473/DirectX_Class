#pragma once
#include "CGameObject.h"
class CPlatformCheck :
	public CGameObject
{
public:
	bool bCheck = false;
	Platform * checkedPlatform = NULL;

	virtual void Start();
	virtual void Update(float deltaTime);

	virtual void OnCollision(CGameObject* CollisionObject);
};

