#pragma once
#include "CGameObject.h"
class CScarecrow :
	public CGameObject
{
public:
	CScarecrow();
	~CScarecrow();

	virtual void Start();
	virtual void Update(float deltaTime);
};

