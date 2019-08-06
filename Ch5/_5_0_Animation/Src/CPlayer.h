#pragma once
#include "CGameObject.h"
class CPlayer :
	public CGameObject
{
public:
	virtual void Start();
	virtual void Update(float deltaTime);

	virtual void OnCollision(CGameObject* CollisionObject);

	D3DXVECTOR2 prevPos;
	float prevMoveX;
	float fMoveSpeed = 0;
};

