#pragma once
#include "CGameObject.h"

class Isaac :
	public CGameObject
{
public:
	Isaac();
	~Isaac();

	virtual void Start();
	virtual void Update(float deltaTime);

	virtual void OnCollision(CGameObject* CollisionObject);

	void Move(float deltaTime);
	void HPControl(float deltaTime);
	void DodgeTime(float deltaTime);

	D3DXVECTOR2 prevPos;
	D3DXVECTOR2 prevMove;
	float fMoveSpeed = 0;

	float maxHP;
	float hp;

	float maxMP;
	float mp;

	HPBar * playerHPbar;
	HPBar * playerMPbar;

	bool bDodge;
	float dodgeTimer;
	float dodgeTime;

	IsaacHead * head = NULL;
};

