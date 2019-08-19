#pragma once
#include "CGameObject.h"
class Platform :
	public CGameObject
{
public:
	Platform();
	~Platform();

	virtual void Start();

	D3DXVECTOR2 platformScale;
};

