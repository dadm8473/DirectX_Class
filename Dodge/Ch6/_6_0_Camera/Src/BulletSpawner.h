#pragma once
#include "CGameObject.h"

class BulletSpawner:
	public CGameObject
{
	virtual void Start();
	virtual void Update(float deltaTime);

	float SpawnTimer;
	float Time;
};

