#pragma once
#include "CGameObject.h"
class CGolem :
	public CGameObject
{
public:
	CState<CGolem> * nowState = NULL;

	float moveSpeed;
	bool bFlip = true;

	D3DXVECTOR2 vMove;
	D3DXVECTOR2 prevMove;
	D3DXVECTOR2 prevPos;

	CPlayerCheck * playerCheck;

	CPlatformCheck * platformCheck;

	CEnemyAttackCollider * enemyAttackCollider;

	virtual void Start();
	virtual void Update(float deltaTime);

	bool Move(float deltaTime);
};

