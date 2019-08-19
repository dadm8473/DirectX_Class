#pragma once
#include "Component.h"
class CVectorMove :
	public Component
{
public:
	CVectorMove(CGameObject * p_trnasform) :Component(p_trnasform) {};
	
	D3DXVECTOR2 InitPos;
	D3DXVECTOR2 vMoveVector;
	float fMoveSpeed;
	float fAngle;

	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void Destroy();
};

