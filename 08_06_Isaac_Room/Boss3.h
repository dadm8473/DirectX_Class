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
	void Pattern1(float deltaTime);
	bool pattern1_Use;
	float pat1_Timer;
	float pat1_Time;
	int pat1_Counter;

public:
	void Pattern2(float deltaTime);
	bool pattern2_Use;
	int sum;
	float pat2_Timer;
	float pat2_Time;
	int pat2_Counter;

public:
	void Pattern3(float deltaTime);
	bool pattern3_Use;
	float pat3_Timer;
	float pat3_Time;
	int pat3_Counter;

public:
	void IdlePattern(float deltaTime);
	float idleTimer;
	float idleTime;
	float idle_Attack_Timer;
	float idle_Attack_Time;
	int idle_Attack_Count;

	bool isHited;
	bool isCool;

	void SetIdle();

public:
	float colorTimer;
	float colorTime;
	void HitColorSet(float deltaTime);
};

