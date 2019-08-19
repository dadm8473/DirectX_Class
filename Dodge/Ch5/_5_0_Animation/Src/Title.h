#pragma once
#include "CGameObject.h"
class Title :
	public CGameObject
{
public:
	Title();
	~Title();

	virtual void Start();
	virtual void Update(float deltaTime);
};

