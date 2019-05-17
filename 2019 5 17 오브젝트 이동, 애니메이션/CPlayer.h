#pragma once
class CPlayer : public CMatrix
{
public:
	CPlayer(D3DXVECTOR2 pos);
	virtual void Update(float deltatime);
	virtual void Render(LPD3DXSPRITE sprite);
};

