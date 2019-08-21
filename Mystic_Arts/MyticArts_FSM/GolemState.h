#pragma once
#include "CState.h"
#include "CGolem.h"

class GolemIdle :
	public CState<CGolem>
{
public:
	static GolemIdle * instance;

	virtual void EnterState(CGolem * pObject);
	virtual void UpdateState(CGolem * pObject, float deltaTime);
	virtual void ExitState(CGolem * pObject);
};

class GolemMove :
	public CState<CGolem>
{
public:
	static GolemMove * instance;

	virtual void EnterState(CGolem * pObject);
	virtual void UpdateState(CGolem * pObject, float deltaTime);
	virtual void ExitState(CGolem * pObject);
};

class GolemAttack1 :
	public CState<CGolem>
{
public:
	static GolemAttack1 * instance;
	float timer;
	bool bAttack;

	virtual void EnterState(CGolem * pObject);
	virtual void UpdateState(CGolem * pObject, float deltaTime);
	virtual void ExitState(CGolem * pObject);
};

class GolemAttack2 :
	public CState<CGolem>
{
public:
	static GolemAttack2 * instance;
	float timer;
	bool bAttack;

	virtual void EnterState(CGolem * pObject);
	virtual void UpdateState(CGolem * pObject, float deltaTime);
	virtual void ExitState(CGolem * pObject);
};