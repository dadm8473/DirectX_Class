#include "DXUT.h"
#include "Header.h"

CBullet::CBullet(D3DXVECTOR2 pos, float speed, float moveAngle)
	: CMatrix(), speed(speed), moveAngle(moveAngle)
{
	position = pos;
	center = D3DXVECTOR2(16, 16);
}

void CBullet::Update(float deltaTime)
{
	position.x += sin(moveAngle*(D3DX_PI / 180)) * speed * deltaTime;
	position.y -= cos(moveAngle*(D3DX_PI / 180)) * speed * deltaTime;

	rotation = moveAngle;

	CMatrix::Update(deltaTime);
}

void CBullet::Render(LPD3DXSPRITE sprite)
{
	// 총알 그려주기
	Draw(sprite, gAssetManager->playerBulletTexture);
}
