#pragma once
#include "CGameObject.h"

class CEnemy :
	public CGameObject
{
public:
	virtual void Start();
	virtual void Update(float deltaTime);

	D3DXVECTOR2 prePos;
};