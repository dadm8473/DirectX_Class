#pragma once
#include "IComponent.h"
class Component :
	public IComponent
{
public:
	CGameObject* transform;

	Component() {};
	Component(CGameObject * p_trnasform) : transform(p_trnasform){}

	virtual void Start() {}
	virtual void Update(float deltaTime) {}
	virtual void Destroy() {}
};

