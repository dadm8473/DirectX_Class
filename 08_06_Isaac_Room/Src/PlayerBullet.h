#pragma once
#include "CGameObject.h"
class PlayerBullet :
	public CGameObject
{
public:
	PlayerBullet();
	~PlayerBullet();

	virtual void Start();
	virtual void Update(float deltaTime);

	D3DXVECTOR2 vMoveVector;
	float fMoveSpeed;

	int temp_damage;
};

