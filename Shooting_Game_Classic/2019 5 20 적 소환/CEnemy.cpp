#include "DXUT.h"
#include "Header.h"

CEnemy::CEnemy(D3DXVECTOR2 pos, float speed)
	: CMatrix(), speed(speed)
{
	position = pos;
	center = D3DXVECTOR2(50, 50);
}

void CEnemy::Update(float deltaTime)
{
	position.y += speed * deltaTime;

	CMatrix::Update(deltaTime);
}

void CEnemy::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->enemyTexture);
}
