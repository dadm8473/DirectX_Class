#pragma once
class CMap
{
public:
	CMatrix mapLayer[2];

public:
	CMap();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};

