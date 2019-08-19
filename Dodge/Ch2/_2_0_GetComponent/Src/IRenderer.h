#pragma once

class IRenderer
{
public:
	virtual void Create(const WCHAR * filename) = 0;
	virtual void Render(D3DXMATRIX mWorld) = 0;
	virtual void Destroy() = 0;
};
