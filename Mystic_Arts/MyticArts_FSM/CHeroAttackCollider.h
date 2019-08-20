#pragma once
#include "CGameObject.h"

class CHeroAttackCollider :
	public CGameObject
{
public:
	CHeroAttackCollider();
	~CHeroAttackCollider();

	CGameObject * parent;
	D3DXVECTOR2 attackVector;
	float attackPower;

	int collisionNum = 0;

	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void OnCollision(CGameObject* CollisionObject);
};

