#pragma once
class CMatrix
{
public:
	D3DXMATRIX matrix;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR2 center;
	float rotation;

	int a, r, g, b;

	// 애니메이션
	bool animation;

	float aniTime, aniTimer;
	int currentScene, maxScene;
	bool repeatAni, isAniEnd;

public:
	CMatrix();
	virtual void Update(float deltaTime);
	void Draw(LPD3DXSPRITE sprite, CTexture* texture);
	virtual void SetAnimation(float rate, int maxScene, bool repeat);
};

