#include "DXUT.h"
#include "Header.h"

CBullet::CBullet(D3DXVECTOR2 pos, float speed, float moveAngle)
	: CMatrix(), speed(speed), moveAngle(moveAngle), isDestroyed(false)
{
	position = pos;
	center = D3DXVECTOR2(16, 16);
}

void CBullet::Update(float deltaTime)
{
	position.x += sin(D3DXToRadian(moveAngle)) * speed * deltaTime;
	position.y -= cos(D3DXToRadian(moveAngle)) * speed * deltaTime;

	rotation = moveAngle;

	if (position.y < 0 - 100)
		isDestroyed = true;

	CMatrix::Update(deltaTime);

	SetRect(&rect, position.x - 16, position.y - 16, position.x + 16, position.y + 16);
}

void CBullet::Render(LPD3DXSPRITE sprite)
{
	// 총알 그려주기
	Draw(sprite, gAssetManager->playerBulletTexture);
}
