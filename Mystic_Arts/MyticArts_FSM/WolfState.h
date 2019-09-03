#pragma once
#include "CState.h"
#include "CWolf.h"

class WolfIdle :
	public CState<CWolf>
{
public:
	static WolfIdle * instance;

	virtual void EnterState(CWolf * pObject);
	virtual void UpdateState(CWolf * pObject, float deltaTime);
	virtual void ExitState(CWolf * pObject);
};

class WolfMove :
	public CState<CWolf>
{
public:
	static WolfMove * instance;

	virtual void EnterState(CWolf * pObject);
	virtual void UpdateState(CWolf * pObject, float deltaTime);
	virtual void ExitState(CWolf * pObject);
};

class WolfJump :
	public CState<CWolf>
{
public:
	static WolfJump * instance;

	virtual void EnterState(CWolf * pObject);
	virtual void UpdateState(CWolf * pObject, float deltaTime);
	virtual void ExitState(CWolf * pObject);
};

class WolfFall :
	public CState<CWolf>
{
public:
	static WolfFall * instance;
	bool jump2fall;

	virtual void EnterState(CWolf * pObject);
	virtual void UpdateState(CWolf * pObject, float deltaTime);
	virtual void ExitState(CWolf * pObject);
};


class WolfAttack :
	public CState<CWolf>
{
public:
	static WolfAttack * instance;


	virtual void EnterState(CWolf * pObject);
	virtual void UpdateState(CWolf * pObject, float deltaTime);
	virtual void ExitState(CWolf * pObject);
};

class WolfHitted :
	public CState<CWolf>
{
public:
	static WolfHitted * instance;

	virtual void EnterState(CWolf * pObject);
	virtual void UpdateState(CWolf * pObject, float deltaTime);
	virtual void ExitState(CWolf * pObject);
};


class WolfDown :
	public CState<CWolf>
{
public:
	static WolfDown * instance;

	virtual void EnterState(CWolf * pObject);
	virtual void UpdateState(CWolf * pObject, float deltaTime);
	virtual void ExitState(CWolf * pObject);
};

