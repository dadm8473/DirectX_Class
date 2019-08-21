#pragma once
#include "CState.h"
#include "CHero.h"

class HeroIdle :
	public CState<CHero>
{
public:
	static HeroIdle * instance;

	virtual void EnterState(CHero * pObject);
	virtual void UpdateState(CHero * pObject, float deltaTime);
	virtual void ExitState(CHero * pObject) ;
};

class HeroMove :
	public CState<CHero>
{
public:
	static HeroMove * instance;

	virtual void EnterState(CHero * pObject);
	virtual void UpdateState(CHero * pObject, float deltaTime) ;
	virtual void ExitState(CHero * pObject) ;
};

class HeroJump :
	public CState<CHero>
{
public:
	static HeroJump * instance;
	bool isDoubleJump;

	virtual void EnterState(CHero * pObject);
	virtual void UpdateState(CHero * pObject, float deltaTime) ;
	virtual void ExitState(CHero * pObject) ;
};

class HeroFall :
	public CState<CHero>
{
public:
	static HeroFall * instance;
	bool jump2fall;

	virtual void EnterState(CHero * pObject);
	virtual void UpdateState(CHero * pObject, float deltaTime) ;
	virtual void ExitState(CHero * pObject) ;
};

class HeroInAir :
	public CState<CHero>
{
public:
	static HeroInAir * instance;
	int index;

	bool isSkyAttack = false;

	virtual void EnterState(CHero * pObject);
	virtual void UpdateState(CHero * pObject, float deltaTime);
	virtual void ExitState(CHero * pObject);
};

class HeroAttack :
	public CState<CHero>
{
public:
	static HeroAttack * instance;
	int combo;
	int comboInput;
	float timer;

	virtual void EnterState(CHero * pObject);
	virtual void UpdateState(CHero * pObject, float deltaTime);
	virtual void ExitState(CHero * pObject);
};

class HeroSkyAttack :
	public CState<CHero>
{
public:
	static HeroSkyAttack * instance;
	int combo;
	int comboInput;
	float timer;

	bool under_Attack;

	virtual void EnterState(CHero * pObject);
	virtual void UpdateState(CHero * pObject, float deltaTime);
	virtual void ExitState(CHero * pObject);
};

class HeroSpecailAttack :
	public CState<CHero>
{
public:
	static HeroSpecailAttack * instance;
	int index;
	float timer;

	virtual void EnterState(CHero * pObject);
	virtual void UpdateState(CHero * pObject, float deltaTime);
	virtual void ExitState(CHero * pObject);
};

class HeroGuard :
	public CState<CHero>
{
public:
	static HeroGuard * instance;

	virtual void EnterState(CHero * pObject);
	virtual void UpdateState(CHero * pObject, float deltaTime);
	virtual void ExitState(CHero * pObject);
};