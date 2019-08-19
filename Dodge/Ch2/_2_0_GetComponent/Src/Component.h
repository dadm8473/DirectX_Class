#pragma once
#include "IComponent.h"
class Component :
	public IComponent
{
public:
	Component() {};
	Component(CTransform * p_trnasform) : transform(p_trnasform){};

	CTransform* transform;

	virtual void Start() { MessageBoxA(NULL, "Component Not Included", "Err", MB_ICONERROR); };
	virtual void Update(float deltaTime) {};
	virtual void Destroy() {};
};

