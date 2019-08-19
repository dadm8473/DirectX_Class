#pragma once
#include "CGameObject.h"
class EnemyHall :
	public CGameObject
{
public:
	EnemyHall();
	~EnemyHall();

	virtual void Start();
	virtual void Update(float deltaTime);

	D3DXVECTOR2 prevPos;
	D3DXVECTOR2 vMoveVector;
	float fMoveSpeed;

	float Timer;
	float Time;
};

