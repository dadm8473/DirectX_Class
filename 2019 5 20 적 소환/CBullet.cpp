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
	position.x += sin(D3DXToRadian(moveAngle)) * speed * deltaTime;
	position.y -= cos(D3DXToRadian(moveAngle)) * speed * deltaTime;

	rotation = moveAngle;

	CMatrix::Update(deltaTime);
}

void CBullet::Render(LPD3DXSPRITE sprite)
{
	// �Ѿ� �׷��ֱ�
	Draw(sprite, gAssetManager->playerBulletTexture);
}
