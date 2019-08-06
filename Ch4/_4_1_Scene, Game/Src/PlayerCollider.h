#pragma once
#include "DXUT.h"
#include "CTransform.h"
#include "Collider.h"
class PlayerCollider :
	public Collider
{
public:
	PlayerCollider(CGameObject * transform, int p_Layer) : Collider(transform, p_Layer)
	{
		Type = CT_CIRCLE;
		scale = { 5, 5 };
	}
};

