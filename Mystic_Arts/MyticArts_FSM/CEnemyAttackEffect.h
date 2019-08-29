#pragma once
#include "CGameObject.h"
class CEnemyAttackEffect :
	public CGameObject
{
public:
	CEnemyAttackEffect();
	~CEnemyAttackEffect();

	virtual void Start();
	virtual void Update(float deltaTime);
};

