#pragma once
#include "CGameObject.h"
class CPlayer :
	public CGameObject
{
public:
	virtual void Start();
	virtual void Update(float deltaTime);

	virtual void OnCollision(CGameObject* CollisionObject);

	void Move(float deltaTime);
	void HPControl(float deltaTime);
	void MPControl(float deltaTime);
	void DodgeTime(float deltaTime);

	D3DXVECTOR2 prevPos;
	float prevMoveX;
	float fMoveSpeed = 0;

	float maxHP;
	float hp;
	HPBar * playerHPbar;

	float maxMP;
	float mp;
	HPBar * playerMPbar;

	bool bDodge;
	float dodgeTimer;
	float dodgeTime;
};

