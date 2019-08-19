#pragma once
#include "CTransform.h"
class CGameObject :
	public CTransform
{
public:
	Renderer * m_Renderer;

public:
	CGameObject();

	virtual ~CGameObject();

	virtual void Init() {};

	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void Destroy();
};

