#pragma once
class CScene;
class CPlayer : public CMatrix
{
public:
	CScene* parentScene;

	float attackTimer;
	float attackTime;

	bool isAttacking;

	RECT rect;

public:
	CPlayer(D3DXVECTOR2 pos);
	virtual void Update(float deltatime);
	virtual void Render(LPD3DXSPRITE sprite);

	void Attack();
};

