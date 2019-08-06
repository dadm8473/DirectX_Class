#pragma once
#include "CGameObject.h"

class BulletSpawner :
	public CGameObject
{
public:
	EnemyBullet* bullet;

	D3DXVECTOR2 prePos;

	int attackCount;
	int maxAttackCount;

	float attackTime;
	float attackTimer;

	int movedir_x;

public:
	virtual void Start();
	virtual void Update(float deltaTime);
};