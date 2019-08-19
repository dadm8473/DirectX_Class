#pragma once
#include "CGameObject.h"
class ChaseEnemy :
	public CGameObject
{
public:
	ChaseEnemy();
	~ChaseEnemy();

	virtual void Start();
	virtual void Update(float deltaTime);

	virtual void OnCollision(CGameObject* CollisionObject);

	D3DXVECTOR2 prevPos;
	D3DXVECTOR2 vMoveVector;
	float fMoveSpeed;

	float maxHP;
	float hp;

	float activeTimer;
	float activeTime;

	float colorTimer;
	float colorTime;
	void HitColorSet(float deltaTime);
};

