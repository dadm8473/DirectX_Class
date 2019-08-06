#pragma once
#include "Component.h"
class CTitleControl :
	public Component
{
public:
	CTitleControl(CGameObject * p_trnasform) :Component(p_trnasform) {};

	virtual void Update(float deltaTime);
};

