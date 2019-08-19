#pragma once
#include "CGameObject.h"
#include "CState.h"

class CHero :
	public CGameObject
{
public:
	CHero();
	~CHero();

	CState<CHero> * nowState = NULL;

	float moveSpeed;
	bool bFlip = true;
	D3DXVECTOR2 prevMove;
	D3DXVECTOR2 prevPos;

	virtual void Start();
	virtual void Update(float deltaTime);

	bool Move(float deltaTime);
};

