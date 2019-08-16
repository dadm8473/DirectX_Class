#pragma once
#include "CGameObject.h"

class ChaseBall :
	public CGameObject
{
public:
	ChaseBall();
	~ChaseBall();

	virtual void Start();
	virtual void Update(float deltaTime);

	virtual void OnCollision(CGameObject* CollisionObject);

	D3DXVECTOR2 prevPos;
	D3DXVECTOR2 vMoveVector;
	float fMoveSpeed;

	float maxHP;
	float hp;

	float colorTimer;
	float colorTime;
	void HitColorSet(float deltaTime);
};

