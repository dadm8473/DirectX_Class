#pragma once
#include "CGameObject.h"
class CWolf :
	public CGameObject
{
public:
	CWolf();
	~CWolf();

	CState<CWolf> * nowState = NULL;

	float moveSpeed;
	bool bFlip = true;

	D3DXVECTOR2 vMove;
	D3DXVECTOR2 prevMove;
	D3DXVECTOR2 prevPos;

	CPlayerCheck * playerCheck;

	CPlatformCheck * platformCheck;
	CPlatformCheck * jumpPlatformCheck;

	CEnemyAttackCollider * enemyAttackCollider;

	// AttackState º¯¼ö
	float timer;

	virtual void Start();
	virtual void Update(float deltaTime);

	bool Move(float deltaTime);
};

