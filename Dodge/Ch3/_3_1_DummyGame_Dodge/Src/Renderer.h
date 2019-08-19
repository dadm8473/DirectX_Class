#pragma once
#include "IRenderer.h"
class Renderer :
	public IRenderer
{
public :
	CTexture* m_pTexture;

	virtual void Create(const WCHAR* filename) {};
	virtual void Render(D3DXMATRIX mWorld) {};
	virtual void Destroy() {};

	virtual CTexture * GetTextureInfo() 
	{
		return m_pTexture;
	}
};

