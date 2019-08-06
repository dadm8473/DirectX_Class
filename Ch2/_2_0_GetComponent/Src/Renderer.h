#pragma once
#include "IRenderer.h"
class Renderer :
	public IRenderer
{
public :

	virtual void Create(const WCHAR* filename) {};
	virtual void Render(D3DXMATRIX mWorld) {};
	virtual void Destroy() {};
};

