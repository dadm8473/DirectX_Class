#pragma once
#include "CGameObject.h"
class EnemyBullet :
	public CGameObject
{
public:
	virtual void Start();
	virtual void Update(float deltaTime);

	D3DXVECTOR2 InitPos;
	D3DXVECTOR2 vMoveVector;
	float fMoveSpeed = 600;
};

