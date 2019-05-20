#pragma once
class CBullet : public CMatrix
{
public:
	float speed;
	float moveAngle;

public:
	CBullet(D3DXVECTOR2 pos, float speed, float moveAngle);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};