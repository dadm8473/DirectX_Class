#pragma once
#include "CGameObject.h"

class CItem :
	public CGameObject
{
public:
	int type;

public:
	CItem(int type);
	~CItem();

	virtual void Start();
	virtual void Update(float deltaTime);

	virtual void OnCollision(CGameObject* CollisionObject);
};

