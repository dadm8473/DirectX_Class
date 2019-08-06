#pragma once
#include "DXUT.h"
#include "CTransform.h"
#include "Collider.h"
class BulletCollider :
	public Collider
{
public:
	BulletCollider(CGameObject * transform, int p_Layer) : Collider(transform, p_Layer)
	{
		Type = CT_BOX;
		scale = { 5, 5 };
	}

	virtual void OnCollision(CGameObject * CollisionObject);
};

