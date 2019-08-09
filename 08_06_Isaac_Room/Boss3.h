#pragma once
#include "CGameObject.h"

class Boss3 :
	public CGameObject
{
public:
	Boss3();
	~Boss3();

	virtual void Start();
	virtual void Update(float deltaTime);

	virtual void OnCollision(CGameObject* CollisionObject);

	void Move(float deltaTime);
	void HPControl(float deltaTime);

public:
	int phase;

	void PhaseControl(float deltaTime);

	float transTime;
	float transTimer;

public:
	D3DXVECTOR2 vMoveVector;

	D3DXVECTOR2 prevPos;
	float fMoveSpeed = 0;
	float pAngle;

	int pos_x;
	int pos_y;

	float moveTime;
	float moveTimer;

public:
	bool bDie;
	float maxHP;
	float hp;

	HPBar * bossHPBar;

public:
	bool bPattern;
	int patternIndex;
	float Timer;
	float Time;
	void PatternUse(float deltaTime);

public:
	float colorTimer;
	float colorTime;
	void HitColorSet(float deltaTime);
};

