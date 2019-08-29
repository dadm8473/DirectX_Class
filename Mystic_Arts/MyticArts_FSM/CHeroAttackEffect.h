#pragma once
#include "CGameObject.h"
class CHeroAttackEffect :
	public CGameObject
{
public:
	CHeroAttackEffect();
	~CHeroAttackEffect();

	virtual void Start();
	virtual void Update(float deltaTime);
};

