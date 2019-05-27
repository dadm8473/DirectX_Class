#include "DXUT.h"
#include "Header.h"

CEnemy::CEnemy(D3DXVECTOR2 pos, float speed)
	: CMatrix(), speed(speed), isDestroyed(false), hp(3)
{
	position = pos;
	center = D3DXVECTOR2(50, 50);
}

void CEnemy::Update(float deltaTime)
{
	position.y += speed * deltaTime;

	if (position.y > 768 + 100 || hp < 0)
		isDestroyed = true;

	CMatrix::Update(deltaTime);

	SetRect(&rect, position.x - 50, position.y - 50, position.x + 50, position.y + 50);
}

void CEnemy::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->enemyTexture);
}
