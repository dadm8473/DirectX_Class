#pragma once
#include "CGameObject.h"
class Wall :
	public CGameObject
{
public:
	virtual void Start();

	D3DXVECTOR2 platformScale;
};

