#pragma once
#include "Renderer.h"
class CSpriteRenderer :
	public Renderer
{
public:
	LPD3DXSPRITE m_Sprite;
	int r, g, b, a;

	virtual void Create(const WCHAR* filename);
	virtual void Render(D3DXMATRIX mWorld);
	virtual void Destroy();
};
