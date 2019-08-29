#pragma once
#include "CGameObject.h"

class CEnemyAttackCollider:
	public CGameObject
{
public:
	CEnemyAttackCollider();
	~CEnemyAttackCollider();

	CGameObject * parent;
	D3DXVECTOR2 attackVector;
	float attackPower;

	int collisionNum = 0;

	CEnemyAttackEffect * attackEffect;
	D3DXVECTOR2 effectPos = { 0,0 };

	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void OnCollision(CGameObject* CollisionObject);
};

