#pragma once
#include "CGameObject.h"
class EnemyBullet :
	public CGameObject
{
public:
	float moveAngle = 0;

public:
	virtual void Init();
};

