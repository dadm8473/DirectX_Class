#pragma once
#include "CGameObject.h"
class IsaacHead :
	public CGameObject
{
public:
	IsaacHead();
	~IsaacHead();

	virtual void Start();
	virtual void Update(float deltaTime);

	D3DXVECTOR2 prevAttack;
	D3DXVECTOR2 moveVector;
	int moveDir = 0;

	int sum;

	float attackTime;
	float attackTimer;
};

