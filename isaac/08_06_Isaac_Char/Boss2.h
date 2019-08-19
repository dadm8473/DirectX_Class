#pragma once
#include "CGameObject.h"
class Boss2 :
	public CGameObject
{
public:

	virtual void Start();
	virtual void Update(float deltaTime);

	virtual void OnCollision(CGameObject* CollisionObject);

	void Move(float deltaTime);
	void HPControl(float deltaTime);

	D3DXVECTOR2 vMoveVector;

	D3DXVECTOR2 prevPos;
	float fMoveSpeed = 0;

	bool bDie;
	float maxHP;
	float hp;

	HPBar * bossHPBar;

	bool bPattern;
	int patternIndex;
	float Timer;
	float Time;

	bool isAttack;

	void PatternUse(float deltaTime);

	float colorTimer;
	float colorTime;
	void HitColorSet(float deltaTime);
};

