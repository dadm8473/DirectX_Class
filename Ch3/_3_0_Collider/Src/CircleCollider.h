#pragma once
#include "DXUT.h"
#include "CTransform.h"
#include "Collider.h"
class PlayerCollider :
	public Collider
{
public:
	PlayerCollider(CGameObject * transform, int p_Layer) : Collider(transform)
	{
		Type = CT_BOX;
		scale = { 5, 5 };
	}
};

