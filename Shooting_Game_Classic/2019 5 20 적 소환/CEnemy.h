#pragma once
class CEnemy : public CMatrix
{
public:
	float speed;

public:
	CEnemy(D3DXVECTOR2 pos, float speed = 300);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};

