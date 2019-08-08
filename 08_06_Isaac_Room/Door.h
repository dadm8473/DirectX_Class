#pragma once
#include "CGameObject.h"
class Door :
	public CGameObject
{
public:
	Door();
	~Door();

	int dir = DOWN;

	D3DXVECTOR2 nextRoom;

	virtual void Start();
	virtual void OnCollision(CGameObject* CollisionObject);
};

