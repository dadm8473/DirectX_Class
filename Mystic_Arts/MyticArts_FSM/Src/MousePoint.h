#pragma once
#include "CGameObject.h"
class MousePoint :
	public CGameObject
{
public:
	MousePoint();
	~MousePoint();

	virtual void Start();

	virtual void Update(float deltaTime);
};

