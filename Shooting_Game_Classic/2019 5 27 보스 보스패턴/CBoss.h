#pragma once

class CScene;
class CBoss : public CMatrix
{
public:
	CScene* parentScene;

	int hp;
	int maxHp;
	int speed;

	bool isEnter;
	bool isPatternOn;

	int patternNum;
	int sum;

	int bulletCount, maxBullet;
	float patternTimer, patternTime;
	float attackTimer, attackTime;
	
	bool isDie;
	RECT rect;

public:
	CBoss(D3DXVECTOR2 pos);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};

